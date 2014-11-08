#include <iostream>
#include <windows.h>

#define MAX_BUFFER_SIZE 128

using namespace std;

HANDLE pipe;
char readBuffer[MAX_BUFFER_SIZE];

int createPipe(void) {
	wcout << "Creating an instance of a named pipe..." << endl;

	// Create a pipe to send data
	pipe = CreateNamedPipe(
		"\\\\.\\pipe\\DetectionSystem", // name of the pipe
		PIPE_ACCESS_DUPLEX, // 1-way pipe -- send only
		PIPE_TYPE_BYTE, // send data as a byte stream
		1, // only allow 1 instance of this pipe
		0, // no outbound buffer
		0, // no inbound buffer
		0, // use default wait time
		NULL // use default security attributes
		);

	if (pipe == NULL || pipe == INVALID_HANDLE_VALUE) {
		wcout << "Failed to create pipe instance.";
		// look up error code here using GetLastError()
		system("pause");
		return 1;
	}
}

int waitForClient() 
{
	wcout << "Waiting for a client to connect to the pipe..." << endl;

	// This call blocks until a client process connects to the pipe
	BOOL result = ConnectNamedPipe(pipe, NULL);
	if (!result) {
		wcout << "Failed to make connection on named pipe." << endl;
		// look up error code here using GetLastError()
		CloseHandle(pipe); // close the pipe
		system("pause");
		return 1;
	}
}

BOOL writeToPipe(char message[])
{
	wcout << "Sending data to pipe..." << endl;

	// This call blocks until a client process reads all the data
	//char data[] = "Hello";
	DWORD numBytesWritten = 0;
	BOOL result = WriteFile(
		pipe, // handle to our outbound pipe
		message, // data to send
		strlen(message) * sizeof(char), // length of data to send (bytes)
		&numBytesWritten, // will store actual amount of data sent
		NULL // not using overlapped IO
		);

	if (result) {
		wcout << "Number of bytes sent: " << numBytesWritten << endl;
	}
	else {
		wcout << "Failed to send data." << endl;
		// look up error code here using GetLastError()
	}

	return result;
}

void readFromPipe(void)
{
	wcout << "Reading data from pipe..." << endl;

	// The read operation will block until there is data to read
	DWORD numBytesRead = 0;
	BOOL result = ReadFile(
		pipe,
		readBuffer, // the data from the pipe will be put here
		MAX_BUFFER_SIZE * sizeof(char), // number of bytes allocated
		&numBytesRead, // this will store number of bytes actually read
		NULL // not using overlapped IO
		);

	if (result) {
		readBuffer[numBytesRead / sizeof(char)] = '\0'; // null terminate the string
		wcout << "Number of bytes read: " << numBytesRead << endl;
		wcout << "Message: " << readBuffer << endl;
	}
	else {
		wcout << "Failed to read data from the pipe." << endl;
	}
}

int main(int argc, const char **argv)
{
	createPipe();

	waitForClient();


	//readFromPipe();
	//writeToPipe("HELLO"):

    // Close the pipe (automatically disconnects client too)
    CloseHandle(pipe);

    wcout << "Done." << endl;

    system("pause");
    return 0;
}