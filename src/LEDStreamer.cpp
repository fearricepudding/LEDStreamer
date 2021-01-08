#include <boost/thread.hpp>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <boost/asio.hpp>
#include <sstream>
#include "UDPClient.h"
#include<unistd.h>

struct RGB{
	short r;
	short g; 
	short b;
};

struct RGB wheel(uint8_t wheelPos) {
	RGB col;
    if(wheelPos < 85) {
        col.r = (wheelPos * 3);
        col.g = (255 - wheelPos * 3);
        col.b = 0;
    } else if(wheelPos < 170) {
        wheelPos -= 85;
        col.r = (255 - wheelPos * 3);
        col.g = 0;
        col.b = (wheelPos * 3);
    } else {
        wheelPos -= 170;
        col.r = 0;
        col.g = (wheelPos * 3);
        col.b = (255 - wheelPos * 3);
    }
    return col;
}

std::string rgb2hex(int r, int g, int b){ 
	std::stringstream ss; 
	ss << std::setfill('0') << std::setw(2) << std::hex << (r << 16 | g << 8 | b);
	std::stringstream zeros;
	if((ss.str().length()) != 6){
		for(int i = 0; i < (6-ss.str().length()); i++){
			zeros << "0";
		}
	} 	
	return zeros.str() + ss.str();
 }
 
int main(int argc, char *argv[]){
	UdpClient *udp = new UdpClient();
	udp->open();
	
	/*

	Theater chase
	
	// Create our pattern
	std::stringstream payload;
	payload << "0D";
	std::stringstream hex;
	int flipper = 0;
	for(int i = 0; i < 191; i++){
		if(flipper <= 15){
			hex << "FFFFFF";
		}else if( flipper <= 27){
			hex << "FF0000";
		}else{
			hex << "FFFFFF";
			flipper = 0; 
		}
		flipper++;
	}
	payload << hex.str();
	std::string pack = payload.str();		
	char *cstr = new char[pack.length() + 1];
	strcpy(cstr, pack.c_str());
	udp->send(cstr);

	std::string currentHex;
	currentHex = hex.str();

	while(true){

		int current = 191/6;
		std::stringstream payload;
		payload << "0D";
		std::stringstream newHex;
		std::string oldHex = currentHex;
		std::string tomove = oldHex.substr(0, 6);
		oldHex.erase(0, 6);
		newHex << oldHex;
		newHex << tomove;
		payload << newHex.str();
		std::string pack = payload.str();		
		char *cstr = new char[pack.length() + 1];
		strcpy(cstr, pack.c_str());
		udp->send(cstr);
		currentHex = newHex.str();

		//usleep(90000);
	}

	*/



	// RAINBOW CYCLE
	while(true){
		uint16_t i, j;
		for(j=0; j<256; j++) { //256
		std::stringstream payload;
		payload << "0D"; // Add the command first

		    for(i=0; i<191; i++) {
		        RGB newCol = wheel(((i * 256 / 191) + j) & 255);
		        std::string hex = rgb2hex(newCol.r, newCol.g, newCol.b);
		        payload << hex;
		    }
		    
			std::string pack = payload.str();		
			char *cstr = new char[pack.length() + 1];
			strcpy(cstr, pack.c_str());
			udp->send(cstr);
			//
		}
	}

	return 0;
}



