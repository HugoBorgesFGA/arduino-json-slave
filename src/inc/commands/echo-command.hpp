/*
 * echo-command.h
 *
 *  Created on: Oct 9, 2018
 *      Author: hugo
 */

#ifndef SRC_INC_COMMANDS_ECHO_COMMAND_HPP_
#define SRC_INC_COMMANDS_ECHO_COMMAND_HPP_

#include "command.hpp"

class EchoCommand : Command {

public:
	const char* getName();
	unsigned int exec(JsonObject& input, JsonObject& output);
};



#endif /* SRC_INC_COMMANDS_ECHO_COMMAND_HPP_ */
