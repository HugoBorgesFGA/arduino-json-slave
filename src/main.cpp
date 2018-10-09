#include "Arduino.h"

#include "command-manager.hpp"

#define JSON_BUFFER_SIZE 192

CommandManager cmdManager;

char serialBuffer[JSON_BUFFER_SIZE] = {0};
char serialOutputBuffer[JSON_BUFFER_SIZE] = {0};
unsigned int serialBufferpos = 0;

void setup()
{
	// Setup serial port
	Serial.begin(115200);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB
	}
}

void resetCommandBuffer() {
	memset(serialBuffer, 0, sizeof(serialBuffer));
	serialBufferpos = 0;
}

void loop() {

	if (Serial.available() > 0) {
		char inByte = Serial.read();
		if (inByte != '\n'){
			if (serialBufferpos == JSON_BUFFER_SIZE) {
				// Buffer overflow
				resetCommandBuffer();
				return;
			}
			serialBuffer[serialBufferpos++] = inByte;
		}else{
			serialBuffer[serialBufferpos] = '\0';

			// Looks for the first '{'
			unsigned int i = 0;
			for(i = 0; i < serialBufferpos; i++){
				if (serialBuffer[i] == '{'){
					cmdManager.parse(&serialBuffer[i], serialOutputBuffer, sizeof(serialOutputBuffer));
					break;
				}
			}

			Serial.flush();
			resetCommandBuffer();
		}
	}
}
