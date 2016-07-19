/*
 * Created by Kleber Kruger on 08/07/16.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KRUGERLIBS_CONFIGFILE_H
#define KRUGERLIBS_CONFIGFILE_H

#include <mbed.h>
#include <fstream>
#include <iostream>
#include <map>

namespace std {

//inline std::string to_string(short value) {
//
//	return buf;
//}
//inline std::string to_string(int value) {
//	char buf[32];
//	std::sprintf(buf, "%d", value);
//	return buf;
//}
//inline std::string to_string(long value) {
//	char buf[32];
//	std::sprintf(buf, "%ld", value);
//	return buf;
//}
//inline std::string to_string(long long value) {
//	char buf[32];
//	std::sprintf(buf, "%lld", value);
//	return buf;
//}
//inline std::string to_string(unsigned short value) {
//	char buf[32];
//	std::sprintf(buf, "%u", value);
//	return buf;
//}
//inline std::string to_string(unsigned int value) {
//	char buf[32];
//	std::sprintf(buf, "%u", value);
//	return buf;
//}
//inline std::string to_string(unsigned long value) {
//	char buf[32];
//	std::sprintf(buf, "%lu", value);
//	return buf;
//}
//inline std::string to_string(unsigned long long value) {
//	char buf[32];
//	std::sprintf(buf, "%llu", value);
//	return buf;
//}
//inline std::string to_string(float value) {
//	char buf[32];
//	std::sprintf(buf, "%f", value);
//	return buf;
//}
//inline std::string to_string(double value) {
//	char buf[32];
//	std::sprintf(buf, "%f", value);
//	return buf;
//}
//inline std::string to_string(long double value) {
//	char buf[32];
//	std::sprintf(buf, "%Lf", value);
//	return buf;
//}

}

using namespace std;

class ConfigFile {
public:

	ConfigFile(const std::string filePath) :
			filePath(filePath) {
	}

	ConfigFile(const ConfigFile &orig) :
			filePath(orig.filePath), configMap(orig.configMap) {
	}

	virtual ~ConfigFile() {
	}

	char *get(const std::string key) {
		std::string *value = &configMap[key];
		return value != NULL ? (char *) value->c_str() : NULL;
	}

	bool getBool(const std::string key);
	short getShort(const std::string key);
	unsigned short getUShort(const std::string key);
	int getInt(const std::string key);
	unsigned int getUInt(const std::string key);
	long getLong(const std::string key);
	unsigned long getULong(const std::string key);
	long long getLongLong(const std::string key);
	unsigned long long getULongLong(const std::string key);
	float getFloat(const std::string key);
	double getDouble(const std::string key);
	long double getLongDouble(const std::string key);
	char getChar(const std::string key);
	unsigned char getUChar(const std::string key);
	char *getString(const std::string key);

//	void set(const std::string key, const bool value) {}
//	void set(const std::string key, const long long value) {}
//	void set(const std::string key, const unsigned long long value) {}
//	void set(const std::string key, const long double value) {}
//	void set(const std::string key, const char value) {}
//	void set(const std::string key, const unsigned char value) {}
//	void set(const std::string key, const std::string value) {}

	void setBool(const std::string key, const bool value) {
		configMap[key] = value == 0 ? "false" : "true";
	}

	void setShort(const std::string key, const short value) {
		char buf[6];
		std::sprintf(buf, "%d", value);
		configMap[key] = buf;
	}

	void setUShort(const std::string key, const unsigned short value) {
		char buf[6];
		std::sprintf(buf, "%hu", value);
		configMap[key] = buf;
	}

	void setInt(const std::string key, const int value) {
		char buf[11];
		std::sprintf(buf, "%d", value);
		configMap[key] = buf;
	}

	void setUInt(const std::string key, const unsigned int value) {
		char buf[11];
		std::sprintf(buf, "%du", value);
		configMap[key] = buf;
	}

	void setLong(const std::string key, const long value) {
		char buf[11];
		std::sprintf(buf, "%d", (int) value);
		configMap[key] = buf;
	}

	void setULong(const char *key, const unsigned long value) {
		char buf[11];
		std::sprintf(buf, "%lu", value);
		configMap[key] = buf;
	}

	void setLongLong(const std::string key, const long long value) {
		char buf[20];
		std::sprintf(buf, "%ll", value);
		configMap[key] = buf;
	}

	void setULongLong(const std::string key, const unsigned long long value) {
		char buf[20];
		std::sprintf(buf, "%llu", value);
		configMap[key] = buf;
	}

	void setFloat(const std::string key, const float value) {
		char buf[32];
		std::sprintf(buf, "%f", value);
		configMap[key] = buf;
	}

	void setDouble(const std::string key, const double value) {
		char buf[32];
		std::sprintf(buf, "%f", value);
		configMap[key] = buf;
	}

	void setLongDouble(const std::string key, const long double value) {
		char buf[32];
		std::sprintf(buf, "%L", value);
		configMap[key] = buf;
	}

	void setChar(const std::string key, const char value) {
		configMap[key] = value;
	}

	void setUChar(const std::string key, const unsigned char value) {
		configMap[key] = value;
	}

	void setString(const std::string key, const char *value) {
		configMap[key] = value;
	}

	void setString(const std::string key, const std::string value) {
		configMap[key] = value;
	}

	const char *getPath() const {
		return filePath.c_str();
	}

	bool load() {
		return load((FunctionPointer *) NULL);
	}

	bool load(void (*fptr)(void)) {
		if(fptr == NULL){

		}
		FunctionPointer fp;
		fp.attach(fptr);

		return load(&fp);
	}

	template<typename T>
	bool load(T *tptr, void (T::*mptr)(void)) {
		FunctionPointer fp;
		fp.attach(tptr, mptr);

		return load(&fp);
	}

	bool save() {
		return save((FunctionPointer *) NULL);
	}

	bool save(void (*fptr)(void)) {
		FunctionPointer fp;
		fp.attach(fptr);

		return save(&fp);
	}

	template<typename T>
	bool save(T *tptr, void (T::*mptr)(void)) {
		FunctionPointer fp;
		fp.attach(tptr, mptr);

		return save(&fp);
	}

private:

	std::string filePath;
	std::map<const std::string, std::string> configMap;

	bool load(FunctionPointer *callbackFunction) {
		ifstream file(filePath.c_str(), ios::in);
		if (!file.good()) {
//            throw std::runtime_error("File not found");
			if (callbackFunction) {
				callbackFunction->call();
				return false;
			}
		}
		while (!file.eof()) {
			std::string line;
			file >> line;
			std::size_t pos = line.find("=");
			if (pos != std::string::npos) {
				setString(line.substr(0, pos), line.substr(pos + 1, line.size() - pos - 1));
			}
		}
		file.close();
		return true;
	}

	bool save(FunctionPointer *callbackFunction) {
		ofstream file(filePath.c_str(), ios::ate | ios::out);
		for (std::map<std::string, std::string>::iterator it = configMap.begin(); it != configMap.end(); ++it) {
			file << it->first << "=" << it->second << std::endl;
		}
		file.close();
		return true;
	}

};

#endif //KRUGERLIBS_CONFIGFILE_H

