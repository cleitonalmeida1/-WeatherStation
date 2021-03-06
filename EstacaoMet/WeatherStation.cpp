/*
 * WeatherStation.cpp
 *
 *  Created on: 11/03/2016
 *      Author: Cleiton Gonçalves
 */

#include <WeatherStation.h>

WeatherStation::WeatherStation() :
		fs(FILESYSTEM_NAME), logger(FILEPATH_LOG, true), gps(p13, p14) {

	actions[START] = &WeatherStation::init;
	actions[CONFIGURING] = &WeatherStation::config;
	actions[CONFIGURED] = &WeatherStation::start;
	actions[RELOAD_WATCHDOG] = &WeatherStation::reloadWatchdog;
	actions[READ_SENSORS] = &WeatherStation::readSensors;
	actions[SAVE_DATA] = &WeatherStation::_saveData;
	actions[SEND] = &WeatherStation::_send;

}

WeatherStation::~WeatherStation() {
	// TODO Auto-generated destructor stub
}

void WeatherStation::destroy() {
	this->~WeatherStation();
}

WeatherStation* WeatherStation::getInstance() {
	static WeatherStation *station = NULL;

	if (station == NULL)
		station = new WeatherStation();

	return station;
}

void WeatherStation::start() {
	Serial p(USBTX, USBRX);
	while (true) {
		setState(RELOAD_WATCHDOG);

		if (isTimeToRead()) {
			setState(READ_SENSORS);
			setState(SAVE_DATA);
		}
		//injector.start(0.1, cfg.getReadingInterval() - 0.1);

		if (isTimeToSend()) {
			setState(SEND);
		}

		if (cfg.getReadingInterval() >= 60)
			Sleep();
		else
			wait(0.5);

	}

}

void WeatherStation::init() {
	logger.log("INICIANDO");
	/* Load configuration */
	cfg.loadFromFile(FILEPATH_CONFIG);

	/* Save configuration */
	cfg.saveToFile(FILEPATH_CONFIG,
			"# Weather station without implementing fault tolerance");

	/* Reset by watchdog */
	if ((LPC_WDT->WDMOD >> 2) & 1) {

		logger.log("Reset by watchdog."); /* XXX: The log time may be incorrect */

		/* Blink LED 2 */
		blinkLED(LED2, 10, 100);

	} else {

		logger.log("Reset by power-button."); /* XXX: The log time may be incorrect */

		/* Blink LED 1 */
		blinkLED(LED1, 10, 100);
	}

	setState(CONFIGURING);
}

void WeatherStation::config() {

	logger.log("config() - initializing configuration.");

	powerMbed(POWER_ON); 	// Power on mbed
	powerGPS(POWER_OFF); 	// Power off GPS

	PHY_PowerDown(); 		// Disable ethernet to reduce consumption
	//configTimer();			// Configures timer

	wdt.kick(cfg.getWatchdogTime());	// Configures watchdog timer

	logger.log("config() - successfully configured.");

	setState(CONFIGURED);
}

bool WeatherStation::saveInfoFile() {

	FILE *fp = fopen(FILEPATH_INFO, "w"); // Se o arquivo existir, grava por cima.

	if (fp == NULL)
		return false;

	fprintf(fp, "Parameter \t Unit \t Min value \t Max value\n");

	fprintf(fp, "Air temperature \t degrees C \t ? \t ?\n");
	fprintf(fp, "Air humidity \t %% U.R. \t ? \t ?\n");
	fprintf(fp, "Rainfall \t mm \t 0.0 \t ?\n");
	fprintf(fp, "Wind speed \t m/s \t 0.0 \t ?\n");
	fprintf(fp, "Soil humidity \t Epsilon root \t 1.1 \t 5.54\n");
	fprintf(fp, "Soil temperature \t degrees C \t 5.0 \t 50.0\n");
	fprintf(fp, "Solar radiation \t W/m2 \t 0.0 \t 1500\n");
	fprintf(fp, "Leaf wetness \t kohms \t 1.0 \t 3000\n");
	fprintf(fp, "Battery voltage \t Volts \t 0.0 \t 15.0\n\n");

	fprintf(fp, "Serial Number = \t\t %d\n", SERIAL_NUMBER);
	fprintf(fp, "Firmware version = \t %s \t %s \t %s\n", __TIME__, __DATE__,
	__FILE__);

#ifdef GPS_ENABLE
	if (readGPS())
	fprintf(fp, "Latitude = %f \t Longitude= %f\n", gps.latitude, gps.longitude);
	else
	fprintf(fp, "Latitude = ? \t Longitude= \t ?\n");
#endif

	fclose(fp);

	return true;
}

void WeatherStation::reloadWatchdog() {
	Serial p(USBTX, USBRX);
	wdt.kick();

	blinkLED(LED3, 1, 50);
	logger.log("INICIANDO");
	p.printf("REINICIANDO CICLO\n");

}

bool WeatherStation::isTimeToRead() {

	struct tm *timest;
	time_t time_sec;
	static bool reading = false;
	int tmval;

	time(&time_sec);
	timest = localtime(&time_sec);

	tmval = (cfg.getReadingInterval() >= 60) ? timest->tm_min : timest->tm_sec;

	if (tmval % (int) cfg.getReadingInterval())
		reading = false;
	else if (!reading)
		reading = true;
	else
		return false;

	return reading;
}

bool WeatherStation::isTimeToSend() {

	struct tm *timest;
	time_t time_sec;
	static bool sending = false;

	time(&time_sec);
	timest = localtime(&time_sec);

	if ((timest->tm_hour != cfg.getSendTime().tm_hour)
			|| (timest->tm_min != cfg.getSendTime().tm_min))
		sending = false;
	else if (!sending)
		sending = true;
	else
		return false;

	return sending;
}

float WeatherStation::readSensor(int num_pino, float v_ini_par,
		float v_ini_volts, float v_fim_par, float v_fim_volts) {

	AnalogIn ea[] = { (p15), (p16), (p17), (p18), (p19), (p20) };
	float ca, cl, par, lcad;

	ca = (v_fim_par - v_ini_par) / (v_fim_volts - v_ini_volts);
	cl = v_ini_par - ca * v_ini_volts;

	lcad = ea[num_pino - 15].read();
	par = ca * lcad * 3.3 + cl;

	if (ca > 0) {
		if (par < v_ini_par || lcad == 0.0)
			return (-INFINITY);
		if (par > v_fim_par || lcad == 1.0)
			return (INFINITY);
	}

	if (ca < 0) {
		if (par > v_ini_par || lcad == 0.0)
			return (INFINITY);
		if (par < v_fim_par || lcad == 1.0)
			return (-INFINITY);
	}

	return par;
}

void WeatherStation::readSensors() {
	Serial p(USBTX, USBRX);
	p.printf("LENDO SENSORES\n");

	logger.log("readSensors() - initializing readings.");

	powerBattery(POWER_ON); // Liga Vbat e 5Vc
	wait_ms(200); // Tempo para Vbat estabilizar, pois o acionamento do MOSFET é lento (+/- 23ms)

	SHTx::SHT15 sensorTE_UR(p29, p30); 	// DATA, SCK
	sensorTE_UR.setOTPReload(false);
	sensorTE_UR.setResolution(true);

	Anemometer anem(p21);
	Wetting wet(p19, p26, p25);

	wet.config(100, 1000, 1, 3000); // 100kohms, 1000us, 1kohms, 3000k=3Mohms

	data.setTime(time(NULL));

	sensorTE_UR.update();
	sensorTE_UR.setScale(false);

	data.setAnemometer(anem.read());
	data.setPluviometer(pluv.read());
	pluv.resetCount();
	data.setWetting(wet.read() / 1000); // Molhamento [kohms]
	data.setTemperature(26.0);
	data.setHumidity(68.5);
	data.setSoilTemperaure(readSensor(17, 5, 0.320512821, 50, 3.205128205)); // Temperatura do solo [C]
	data.setSoilHumidity(readSensor(16, 1.1, 0, 5.54, 1.0)); // Umidade do solo [raiz de epsilon]
	data.setSolarRadiation(readSensor(18, 0, 0, 1500, 1.5)); // Irradiação solar [W/m2]
	data.setBatteryVoltage(readSensor(15, 0, 0, 15.085714286, 3.3)); // Tensão da bateria [V]

	// Calculates CRC
	data.setCRC(data.calculateCRC());

	powerBattery(POWER_OFF); 	// Desliga Vbat e 5Vc

	printDataInfo(&data, "\t");

	logger.log("readSensors() - finished.");

}

bool WeatherStation::readGPS() {

	Timer tm;

	logger.log("readGPS() - initializing GPS reading.");

	powerGPS(POWER_ON); // Habilita GPS
	tm.start();

	do {

		if (gps.sample()) {

			logger.log("Lock OK");
			logger.log("readGPS() - successfully read.");

			powerGPS(POWER_OFF); // Desabilita GPS
			return true;

		} else
			logger.log("No lock.");

		wait(1.0);

	} while (!gps.lock && tm.read() < 3);

	powerGPS(POWER_OFF); // Habilita GPS

	logger.log("readGPS() - could not read the GPS.");

	return false;
}

void WeatherStation::_saveData() {
	Serial p(USBTX, USBRX);
	p.printf("SALVANDO DADOS\n");
	if (!saveData()) {
		logger.err("Unable to save the data.");
	}
}

bool WeatherStation::saveData() {

	logger.log("saveData() - saving binary file.");

	bool status = data.save(FILEPATH_DATA);

	/* Creates ready file */
	FILE *fp = fopen(FILEPATH_READY, "w");
	if (fp)
		fclose(fp);

	logger.log("saveData() - binary file saved.");

	return status;
}

void WeatherStation::_send() {
	if (!send()) {
		Serial p(USBTX, USBRX);
		p.printf("ENVIANDO DADOS\n");
		logger.warn("Unable to send the data.");
	}
}

bool WeatherStation::send() {

	logger.log("send() - not implemented yet.");

	return true;
}

void WeatherStation::blinkLED(PinName pin, uint8_t count, int interval) {

	if (pin == LED1 || pin == LED2 || pin == LED3 || pin == LED4) {

		DigitalOut led(pin);

		for (uint8_t i = 0; i < count; i++) {
			led = 1;
			wait_ms(interval);
			led = 0;
			wait_ms(interval);
		}
	}
}

void WeatherStation::powerMbed(Energy action) {

	DigitalOut mbed(p23);

	mbed = (action == POWER_ON) ? 0 : 1;
}

void WeatherStation::powerBattery(Energy action) {

	DigitalOut battery(p24);

	battery = (action == POWER_ON) ? 0 : 1;
}

void WeatherStation::powerGPS(Energy action) {

	DigitalOut gps(p9);

	gps = (action == POWER_ON) ? 1 : 0;
}

void WeatherStation::powerLED(Energy action, PinName pin) {

	if (pin == LED1 || pin == LED2 || pin == LED3 || pin == LED4) {

		DigitalOut led(pin);

		led = (action == POWER_ON) ? 1 : 0;
	}
}

void WeatherStation::fatalError(ErrorType error) {

	uint8_t count = (error < 0) ? (error * -3) : (error * 3);

	logger.err("%s",
			(error == ERROR_OPEN_FILE) ? "OpenFileError" :
			(error == ERROR_READ_SENSOR) ? "ReadSensorsError" : "UnknownError");

	blinkLED(LED4, 5, 50);
	wait(1.0);
	blinkLED(LED4, count, 200);
}

void WeatherStation::printConfigInfo() {

	logger.log("%-18s: %u", "numberOfReadings", cfg.getNumberOfReadings());
	logger.log("%-18s: %u", "minCorrectReadings", cfg.getMinCorrectReadings());
	logger.log("%-18s: %s", "readingUnit",
			(cfg.getReadingUnit() == WeatherStationConfig::READING_UNIT_SEC) ?
					"Sec" : "Min");
	logger.log("%-18s: %.1f", "readingInterval",
			(cfg.getReadingUnit() == WeatherStationConfig::READING_UNIT_SEC) ?
					cfg.getReadingInterval() : cfg.getReadingInterval() / 60);
	logger.log("%-18s: %s", "sendTime", cfg.getFormatedTime());
	logger.log("%-18s: %.1f", "watchdogTime", cfg.getWatchdogTime());
}

void WeatherStation::printDataInfo(ReadingData *d, const char *prefix) {

	logger.log("%s Time: %ld", prefix, d->getTime());

	for (int i = 0; i < ReadingData::NUMBER_OF_PARAMETERS; i++)
		logger.log("%s %s: %.6f", prefix, d->getParameterName(i),
				d->getParameterValue(i));

	logger.log("%s CRC: %lu", prefix, d->getCRC());
}

void WeatherStation::setState(WeatherStation::States state) {
	(this->*actions[state])();
}
