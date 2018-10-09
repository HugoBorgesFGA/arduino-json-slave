#include "commands/echo-command.hpp"

const char* EchoCommand::getName(){
	return "ech";
}

unsigned int EchoCommand::exec(JsonObject& input, JsonObject& output){

	return COMMAND_E_SUCCESSFULL;
}
