/* This program was created by Nathan Stathis on the 20/09/2014
*  It facilitates the control of a rotary turntable with the ability
*  to control the turntable using commands sent over TCP
*
*  The program exhibits the following behaviour:
*  1.  Initialisation
*  1.1 Calibrate the turntable and set the turntable to a known starting position
*  1.2 Start the TCP Server
*  2.  Loop
*  2.1 Listen for command over TCP
*  2.2 Interpret command
*  2.3 Execute command
*  2.4 Return to start
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "turntable.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

#define PORT 3000


// Main program functions
void init();
void loop();

// Turntable functions

// TCP functions
void initTCPserver(int portNo);
void readTCPmessage();



// Global variables
int sockfd, newsockfd; // socket file descriptors
char buffer[256]; // the buffer
struct sockaddr_in serv_addr, cli_addr; // structures for storing ip addresses of client and server


int main(int argc, char *argv[])
{
  /*
  TurnInstruction_t instruction;
  Turntable_t turntable;
  initTurntable(&turntable);
  reset_tt(&turntable);
  */
  init();
  loop();
  return 0;
}


void init()
{
  // Calibrate the turntable and set the turntable to a known starting position

  // Start the TCP server
  initTCPserver(PORT);
}

void loop()
{
  TurnInstruction_t instruction;
  Turntable_t turntable;
  initTurntable(turntable);

  int n;
  while(1)
  {
    // Listen for command over TCP
    listen(sockfd,5);
    readTCPmessage();
    printf("Here is the message: %s\n",buffer);
    // Reply to the message
    n = write(newsockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
    //close(newsockfd);
    //close(sockfd);
    // Interpret command
    if(jsonToTurnInstruction(&instruction, buffer))
        printf("unsuccessful json conversion");
    // Execute command
    parseTurnInstruction(&instruction, &turntable);
    // Return to start
    //break;
  }
}



void initTCPserver(int portNo)
{
  // Create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
     error("ERROR opening socket");
  // Initialise server
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portNo);
  // Checks if the requested port is available
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");
}


void readTCPmessage()
{
  // Accepts the client conneciton
  socklen_t clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0)
    error("ERROR on accept");
  // Initialises the receive buffer
  bzero(buffer,256);
  // Reads the message
  int n = read(newsockfd,buffer,255);
  if (n < 0)
    error("ERROR reading from socket");
}
