#ifndef H_COMMAND
#define H_COMMAND

#include <Arduino.h>
#include <ArduinoJson.h>

#define COMMAND_E_SUCCESSFULL 0

class Command {

public:

	virtual const char* getName() const = 0;
	virtual unsigned int exec(JsonObject& input, JsonObject& output) const = 0;
};

#endif
