/*
 =======================================================================================================================
 File       : Logger.cpp
 -----------------------------------------------------------------------------------------------------------------------
 Author     : Kleber Kruger
 Modified by: Cleiton Gonçalves
 Date       : 2016-07-26
 Version    : 1.1
 Copyright  : Campus Coxim - UFMS
 -----------------------------------------------------------------------------------------------------------------------
 Description: Logger Library
 =======================================================================================================================
 */

#include <Logger/Logger.h>

/**
 * Creates log file
 *
 * @param path 			- log file path
 * @param serial_debug	- print debug on serial port
 */
Logger::Logger(const char *log_path, bool serial_debug) :
		log_path(log_path), serial_debug(serial_debug), pc(USBTX, USBRX) {

	pc.baud(115200);
}

Logger::~Logger() {

	/* Nothing to do */
}

int Logger::printLoggerMsg(LoggerEventType type, const char *msg) {

	FILE *fp = fopen(log_path, "a");

	if (!fp)
		return -1;

	int count = 0;

	char *line = strtok((char *) msg, "");
	for (int i = 0; line != NULL; i++) {

		if (i == 0) {
			fprintf(fp, "%s", line);
			if (serial_debug)
				pc.printf("%s", line);

		} else {
			fprintf(fp, "%35s %s\n", "|", line);
			if (serial_debug)
				pc.printf("%35s %s\n", "|", line);
		}

		count += strlen(line);
		line = strtok(NULL, "\n");
	}

	fclose(fp);
	return count;
}

int Logger::log(const char *fmt, ...) {

	char msg[MAX_MSG_SIZE];
	BUILD_LOGGER_STRING(msg, MAX_MSG_SIZE, fmt);

	return printLoggerMsg(EV_LOG, msg);
}

int Logger::warn(const char *fmt, ...) {

	char msg[MAX_MSG_SIZE];
	BUILD_LOGGER_STRING(msg, MAX_MSG_SIZE, fmt);

	return printLoggerMsg(EV_WARN, msg);
}

int Logger::err(const char *fmt, ...) {

	char msg[MAX_MSG_SIZE];
	BUILD_LOGGER_STRING(msg, MAX_MSG_SIZE, fmt);

	return printLoggerMsg(EV_ERR, msg);
}
