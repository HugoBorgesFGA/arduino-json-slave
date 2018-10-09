#ifndef H_COMMAND_MANAGER
#define H_COMMAND_MANAGER

#include <Arduino.h>

#include "command.hpp"

#ifndef COMMAND_LIST_SIZE
#define COMMAND_LIST_SIZE 16
#endif

#define MODULE_CODE 0x0A
#define CREATE_ERROR(MODULE, ERROR_CODE) ((MODULE << 8) | ERROR_CODE)

#define COMMAND_MANAGER_E_INVALID_JSON             CREATE_ERROR(MODULE_CODE, 1)
#define COMMAND_MANAGER_E_MISSING_CMD_NAME         CREATE_ERROR(MODULE_CODE, 2)
#define COMMAND_MANAGER_E_UNKNOWN_CMD_NAME         CREATE_ERROR(MODULE_CODE, 3)

class CommandManager {

private:

	Command *commands[COMMAND_LIST_SIZE];
	unsigned int commandsSize;

	Command *commandByName(const char *cmdName);

public:

	CommandManager();
	~CommandManager();

	bool addSupportedCommand(Command &command);
	void parse(const char *input, char *output, const size_t outputLength);
};

#endif
