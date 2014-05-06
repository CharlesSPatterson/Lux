/*
 * This code was orginally written and developed by the Lux Backend Team
 * at Philadelphia Game Lab:
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * - Jake
 */
#include "socket.h"
#include <iostream>
#include <sys/types.h> // definitions for system types
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> // needed for internet domain routing
#include <string.h>
#include <netdb.h>
#include <stdio.h> // standard libraries

Socket::Socket(int port){
    Setsin_port(htons(port));
    Setsin_family(AF_INET);
    Sets_addr(INADDR_ANY);
}

Socket::Socket(){
    // we need a way to find an open port?
    Setsin_port(htons(2562));
    Setsin_family(AF_INET);
    Sets_addr(INADDR_ANY);
}

void Socket::init(){
    // creates a new socket
    sockfd = socket(sin_family, SOCK_DGRAM, 0);
	if(sockfd < 0){
		error("socket");
	}

    // initializes the buffer to all 0s
	bzero((char *) &serv_addr, sizeof(serv_addr));

	// sets up the port variables
	serv_addr.sin_family = sin_family;
	serv_addr.sin_addr.s_addr = s_addr;
	serv_addr.sin_port = sin_port;

	// print out the port just for fun.
	printf("%d", serv_addr.sin_port);

    // binds the socket to the port
	if (bind(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    	 error("binding");
	}

	fromlen = sizeof(struct sockaddr_in);
}

// needs to recieve the client address pointer
BSONObj Socket::recieve(struct sockaddr_in* cli_addr){
        if(n = recvfrom(sockfd,buf,message_size,0,(struct sockaddr *)&cli_addr,&fromlen) < 0){
			error("Receive");
		}
		write(1,"Received a datagram: ",21);
       	write(1,buf,n);


        BSONObj recieved = mongo::fromjson(buf, message_size);

        if(!recieved){
            fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
            return 1;
        }
        return recieved;
}

void Socket::send(struct sockaddr_in* cli_addr){
        if(n = sendto(sockfd,"Got your message\n",17,0,(struct sockaddr *)&cli_addr,fromlen) < 0){
			error("send");
		}
}

void Socket::send(struct sockaddr_in* cli_addr, std::string message){
        char *msgChar = new char[message.size()+1]
        msgChar[message.size()]=0;
        memcpy(msgChar,message.c_str(),message.size());
        send(*cli_addr, msgChar);
}

 void Socket::send(struct sockaddr_in* cli_addr, char * message[]){
        if(n = sendto(sockfd,message,sizeof(message),0,(struct sockaddr *)&cli_addr,fromlen) < 0){
			error("send");
		}
 }

void Socket::send(struct sockaddr_in* cli_addr, BSONObj BSMessage){
        send(*cli_addr, BSMessage.jsonString());
 }

void Socket::send(std::list<struct sockaddr_in> SocketList, BSONObj BSMessage){
      		for (std::list<struct sockaddr_in>::iterator cli_addr = broadcast->SocketList.begin(); cli_addr != broadcast->SocketList.end(); cli_addr++){
				send(*cli_addr, BSMessage);
      		}
 }

Socket::~Socket(){
    //dtor
}
int main(){
    return 0;
}
// dumps error messages when they occur
void Socket::error(char *msg){
	perror(msg);
	exit(1);
}
