// Pipe.h : 
//

#ifndef Pipe_H
#define Pipe_H

#include <windows.h>

#define MAX_BUFFER_SIZE 128

class Pipe {
	HANDLE pipe;
	char readBuffer[MAX_BUFFER_SIZE];

	std::vector<std::string> Pipe::split(const std::string &s, char delim);
	bool createPipe();
	bool waitForClient();
	bool writeToPipe(const char message[]);
	std::string readFromPipe();

public:
	Pipe();

	bool initPipe();
	void endPipe();
	std::vector<std::string> listenForCommand();
	void returnMessage(std::string message, std::string method);
};

#endif