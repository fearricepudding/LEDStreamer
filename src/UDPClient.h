#ifndef UDPCLIENT_H_INCLUDED
#define UDPCLIENT_H_INCLUDED

#define PORT	 8080 
#define MAXLINE 2048

// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

class UdpClient{

public:
	UdpClient();
	~UdpClient();
	void open();
	void send(char *message);
	
private:
	int l = 0;
	struct sockaddr_in servaddr; 
	char buffer[MAXLINE]; 
	int sockfd;

};	

#endif
