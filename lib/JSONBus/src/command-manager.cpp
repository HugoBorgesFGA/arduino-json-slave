#include "command-manager.hpp"

#include <string.h>

CommandManager::CommandManager(){

	this->commandsSize = 0;
}

CommandManager::~CommandManager(){


}

Command *CommandManager::commandByName(const char *cmdName){

	unsigned int i = 0;
	for(; i < this->commandsSize; i++){

		Command *command = this->commands[i];
		if (strcmp(command->getName(), cmdName) == 0) return command;
	}

	return nullptr;
}

bool CommandManager::addSupportedCommand(Command &command){

	if (this->commandsSize >= COMMAND_LIST_SIZE) return false;

	this->commands[this->commandsSize++] = &command;
	return true;
}

void CommandManager::parse(const char *input, char *output, const size_t outputLength){

	const char *methodName;

	StaticJsonBuffer<192> jsonInputBuffer;
	JsonObject& inputJson = jsonInputBuffer.parseObject(input);

	StaticJsonBuffer<192> jsonOutputBuffer;
	JsonObject& outputJson = jsonOutputBuffer.createObject();

	unsigned char error;
	Command *cmd = nullptr;

	jsonInputBuffer.clear();
	jsonOutputBuffer.clear();

	// Is it a valid JSON?
	if (!inputJson.success()) {
		outputJson["err"] = COMMAND_MANAGER_E_INVALID_JSON;
		goto out;
	}

	// Does it contains the method name?
	if (inputJson.containsKey("cmd") == false) {
		outputJson["err"] = COMMAND_MANAGER_E_MISSING_CMD_NAME;
		goto out;
	}

	methodName = inputJson["cmd"];
	cmd = this->commandByName(methodName);
	if (cmd == nullptr) {
		outputJson["err"] = COMMAND_MANAGER_E_UNKNOWN_CMD_NAME;
		goto out;
	}

	outputJson["cmd"] = methodName;
	error = cmd->exec(inputJson, outputJson);
	if (error) {
		JsonObject& errorJson = jsonOutputBuffer.createObject();

		errorJson["cmd"] = methodName;
		errorJson["err"]  = error;

		errorJson.printTo(output, outputLength);
		return;
	}

	outputJson["err"] = error;

out:
	outputJson.printTo(output, outputLength);
}
