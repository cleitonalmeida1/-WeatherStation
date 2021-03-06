/*
 * WeatherStation.h
 *
 *  Created on: 11/03/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef WEATHERSTATION_H_
#define WEATHERSTATION_H_

#include "mbed.h"
#include "ConfigFile.h"
#include "EthernetPowerControl.h"
#include "GPS.h"
#include "Logger.h"
#include "nRF24L01P.h"
#include "sht15.hpp"
#include "Anemometer.h"
#include "Pluviometer.h"
#include "ReadingData.h"
#include "Watchdog.h"
#include "Wetting.h"
#include "WeatherStationConfig.h"
#include "Timer.h"
#include "FaultInjector/FaultInjector.h"


#define FILESYSTEM_NAME					"local"

#define FILEPATH_CONFIG					"/" FILESYSTEM_NAME "/config.cfg"
#define FILEPATH_LOG					"/" FILESYSTEM_NAME "/log.txt"
#define FILEPATH_DATA					"/" FILESYSTEM_NAME "/data.dat"
#define FILEPATH_INFO					"/" FILESYSTEM_NAME "/info.txt"
#define FILEPATH_READY					"/" FILESYSTEM_NAME "/ready"

class WeatherStation {
public:

	static const int SERIAL_NUMBER = 123456789;

	typedef void (WeatherStation::*Action)();

	typedef enum {
		START = 0, CONFIGURING, CONFIGURED, RELOAD_WATCHDOG,READ_SENSORS, SAVE_DATA, SEND
	} States;

	typedef enum _Energy {
		POWER_ON, POWER_OFF
	} Energy;

	typedef enum {
		NO_ERROR = 0, ERROR_OPEN_FILE = -1, ERROR_READ_SENSOR = -2
	} ErrorType;

	/**
	 * constructor.
	 */
	WeatherStation();

	/**
	 * destructor.
	 */
	virtual ~WeatherStation();

	/**
	 * Get an instance of WeatherStation object.
	 * Singleton Pattern.
	 */
	static WeatherStation *getInstance();

	/**
	 * Start weather station actions (readings, send).
	 */
	virtual void start();

	/**
	 * Destroy the WeatherStation object.
	 */
	virtual void destroy();

	inline const Logger& getLogger() const {
		return logger;
	}

	/**
	 * Initialize weather station.
	 */
	virtual void init();

	/**
	 * Configure weather station.
	 */
	virtual void config();

	/**
	 * Configure timer.
	 */
	void configTimer();

	/**
	 * Save (record on disk) information file.
	 */
	bool saveInfoFile();

	/**
	 * Reload watchdog time.
	 */
	void reloadWatchdog();

	/**
	 * Checks if it's time to read.
	 */
	bool isTimeToRead();

	/**
	 * Checks if it's time to send.
	 */
	bool isTimeToSend();

	/**
	 * Read sensor.
	 *
	 * @param pin_num
	 * @param v_start_par
	 * @param v_start_volts
	 * @param v_end_par
	 * @param v_end_volts
	 */
	float readSensor(int pin_num, float v_start_par, float v_start_volts,
			float v_end_par, float v_end_volts);

	/**
	 * Read all sensors.
	 */
	virtual void readSensors();

	/**
	 * Read GPS.
	 */
	virtual bool readGPS();

	/**
	 * Save data
	 */
	void _saveData();

	/**
	 * Save data
	 */
	bool saveData();

	/**
	 * Send data
	 */
	void _send();

	/**
	 * Send data
	 */
	bool send();

	/**
	 * Blink LED.
	 *
	 * @param pin
	 * @param count
	 * @param interval
	 */
	void blinkLED(PinName pin, uint8_t count, int interval);

	/**
	 * Power on/off mbed
	 */
	void powerMbed(Energy opt);

	/**
	 * Power on/off battery.
	 */
	void powerBattery(Energy opt);

	/**
	 * Power on/off GPS.
	 */
	void powerGPS(Energy opt);

	/**
	 * Power on/off LED.
	 */
	void powerLED(Energy action, PinName pin);

	/**
	 * Called when a fatal error occurs.
	 * XXX: really necessary?
	 */
	void fatalError(ErrorType error);

	/**
	 * Print configuration parameters.
	 * XXX: really necessary?
	 */
	void printConfigInfo();

	/**
	 * Print readings parameters.
	 * XXX: really necessary?
	 */
	void printDataInfo(ReadingData *data, const char *prefix);

	void setState(States state);

private:
	Action actions[5];

	LocalFileSystem fs;
	Logger logger;
	WeatherStationConfig cfg;
	Watchdog wdt;
	Ticker weak;
	Pluviometer pluv;
	GPS gps;

	ReadingData data;

	FaultInjector injector;
};

#endif /* WEATHERSTATION_H_ */
