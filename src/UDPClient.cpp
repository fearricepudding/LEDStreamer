// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include "UDPClient.h"
#include <iostream>

int nopackets = 0;

UdpClient::UdpClient(){};
UdpClient::~UdpClient(){
	close(sockfd); 
}

// Driver code 
void UdpClient::open(){
	 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.222");
//	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
} 

void UdpClient::send(char *message){
	int n; 
	socklen_t len;

	sendto(sockfd, (const char *)message, strlen(message), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
				
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
			MSG_WAITALL, (struct sockaddr *) &servaddr, 
			&len);
			buffer[n] = '\0'; 
			//std::cout << "Response: " << buffer << std::endl;
		
			std::cout << nopackets << " " << std::flush;
		if(l == 0){
			std::cout << "-\r" << std::flush;
		}else if(l == 1){
			std::cout << "\\\r" << std::flush;
		}else if(l == 2){
			std::cout << "|\r" << std::flush;
		}else if(l == 3){
			std::cout << "/\r" << std::flush;
		}else if(l == 4){
			std::cout << "-\r" << std::flush;
			l = 0;
		}
		l++;
		nopackets++;
}
