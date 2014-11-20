// Pipe.cpp : 
//

#include "stdafx.h"
#include "Pipe.h"

Pipe::Pipe(){ }

bool Pipe::initPipe(){
	return createPipe() && 
		waitForClient();
}

std::vector<std::string> Pipe::listenForCommand(){
	std::string input = readFromPipe();
	return split(input, ',');	
}

void Pipe::returnMessage(std::string message, std::string method){
	if (message.length() == 0){
		std::cout << "No output\n";
		return;
	}

	std::cout << "Output: " << message.c_str() << "\n";
	std::cout << "Method: " << method.c_str() << "\n";
	writeToPipe(message.c_str());
}

std::vector<std::string> Pipe::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}

void Pipe::endPipe(){
	std::cout << "Shutting down Detection System\n";

	// Close the pipe (automatically disconnects client too)
	CloseHandle(pipe);

	std::cout << "Done" << std::endl;
}

bool Pipe::createPipe() {
	std::cout << "Creating an instance of a named pipe..." << std::endl;
	// Create a pipe to send data

	pipe = CreateNamedPipeA(
		(LPCSTR)"\\\\.\\pipe\\DetectionSystem", // name of the pipe
		PIPE_ACCESS_DUPLEX, // 2-way pipe
		PIPE_TYPE_BYTE, // send data as a byte stream
		1, // only allow 1 instance of this pipe
		0, // no outbound buffer
		0, // no inbound buffer
		0, // use default wait time
		NULL // use default security attributes
		);

	if (pipe == NULL || pipe == INVALID_HANDLE_VALUE){
		std::cout << "Failed to create pipe instance.";
		return false;
	}

	return true;
}

bool Pipe::waitForClient() 
{
	std::cout << "Waiting for a client to connect to the pipe..." << std::endl;

	bool result = ConnectNamedPipe(pipe, NULL);
	if (!result) {
		std::cout << "Failed to make connection on named pipe." << std::endl;
		std::cout << "Error: " << GetLastError() << "\n";
		CloseHandle(pipe); // close the pipe
		return false;
	}

	return true;
}

bool Pipe::writeToPipe(const char message[])
{
	std::cout << "Sending data to pipe..." << std::endl;

	// This call blocks until a client process reads all the data
	DWORD numBytesWritten = 0;

	bool result = WriteFile(
		pipe, // handle to our outbound pipe
		message, // data to send
		std::strlen(message) * sizeof(char), // length of data to send (bytes)
		&numBytesWritten, // will store actual amount of data sent
		NULL // not using overlapped IO
		);

	if (result) {
		std::cout << "Number of bytes sent: " << numBytesWritten << std::endl;
		std::cout << "Sending end char\n";
		result = WriteFile(
			pipe, // handle to our outbound pipe
			"\n", // data to send
			std::strlen("\n") * sizeof(char), // length of data to send (bytes)
			&numBytesWritten, // will store actual amount of data sent
			NULL // not using overlapped IO
			);
		if (result){
			std::cout << "Flushing pipe\n";
			FlushFileBuffers(pipe);
		} else
			std::cout << "End char failed\n";
	}
	else {
		std::cout << "Failed to send data." << std::endl;
		// look up error code here using GetLastError()
	}

	return result;
}

std::string Pipe::readFromPipe()
{	
	std::cout << "Reading data from pipe..." << std::endl;

	// The read operation will block until there is data to read
	DWORD numBytesRead = 0;
	bool result = ReadFile(
		pipe,
		readBuffer, // the data from the pipe will be put here
		MAX_BUFFER_SIZE * sizeof(char), // number of bytes allocated
		&numBytesRead, // this will store number of bytes actually read
		NULL // not using overlapped IO
		);

	if (result) {
		readBuffer[numBytesRead / sizeof(char)] = '\0'; // null terminate the string
		std::cout << "Number of bytes read: " << numBytesRead << std::endl;
		std::cout << "Message: " << readBuffer << std::endl;
	}
	else {
		std::cout << "Failed to read data from the pipe." << std::endl;
		return "";
	}

	return readBuffer;
}