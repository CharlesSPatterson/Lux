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

#include <iostream>
#include <sys/types.h> // definitions for system types
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> // needed for internet domain routing
#include <string.h>
#include <netdb.h>
#include <stdio.h> // standard libraries
#include <list>
#include <queue>
#include "socket.h"

#define MESSAGE_SIZE 256



// called when a system call fails
void error(char *msg){
	perror(msg);
	exit(1);
}
// information on the connection to the database
typedef struct DBC{
};
typedef struct BGTStruct{
    int port;
    struct DBC DBConnection;
};
typedef struct broadcastStruct{
    // socket list
    std::list<struct sockaddr_in> SocketList;
    // message queue
    std::queue<char*> BroadcastQueue;
    Socket socket;
};


void broadcastThread(struct broadcastStruct *broadcast){
    // establish new sending port
    Socket sendSocket;
	sendSocket.init();
	while(1){
		if(!broadcast->BroadcastQueue.empty()){ // if there is something in the broadcast queue
			for (std::list<struct sockaddr_in>::iterator clientSocket = broadcast->SocketList.begin(); clientSocket != broadcast->SocketList.end(); clientSocket++){
				// this is the send command, but it is not implemeneted in socket.cpp
				sendSocket.send(&*clientSocket,*(broadcast->BroadcastQueue.front()));
			}
			broadcast->BroadcastQueue.pop();
		}
		// otherwise we can probably give up our processor time.
    }
}

void battleGroundThread(struct BGT *BGTData){

    struct broadcastStruct broadcastData();

	// spawn the broadcast thread
	pthread_t BTID;
	pthread_create(&BTID, NULL, void* (*)&broadcastThread, (void *) &broadcastData);


    /*

    should add another thread that decides who needs to know what, sends in a struct of
        socket list of who needs to know
        information
    that should be what is broadcast from the broadcast queue, but worry about that in a few days.

    */

	// open listening port
	Socket socket;
	socket.init();

	broadcastData.socket = socket;

	// update the Port# in the BGT struct
	BGTData->port = socket.Getport();
    struct sockaddr_in cli_addr;
	while(1){
		// listen on port for clients
		socket.recieve(&cli_addr);
		// update the Socket List if the client is new
		// if the socket is updated but the token is the same then just update the socket for the client
		broadcastData.SocketList.push_front(cli_addr);
		// push any messages from clients into Broadcast queue
		//broadcastData.BroadcastQueue.push(socket.GetMessage());
	}
}

int main(int argc, char *argv[]){

    // open a new socket to listen on
    int port = atoi(argv[1]);
    Socket socket(port); // construct a socket
    socket.init(); // initialize it after to give a chance to change variables

    // launch battle ground threads Here
    pthread_t BGTID;
    struct BGTStruct BGT;

    pthread_create(&BGTID, NULL, (void *) &battleGroundThread, (void *) &BGT);


    struct sockaddr_in cli_addr;
	while(1){
		// accept clients, who will send in their "User Token"

		socket.recieve(&cli_addr);
		// this will be how we read the "User Token"
		//socket.GetMessage();
		// add a method to parse the user token and link it to a BGT

		// Send the clients back their BGT port number
		socket.send(&cli_addr);
		//socket.send(&cli_addr, BGT.port);

        // track users and their BGTs here.

        // if a BGT crashes then relaunch it and you will need to know the database it is using
        //

	}
	return 0;
}