TODO:
	Fix the pointers 
	Create a Class Around the main class opposed to a file
	Make sure the ports can properly connect
	Test with simple C++ client (or python maybe)
	
# Workflow

## Forking 

1. go to https://github.com/PhiladelphiaGameLab/Lux
2. Fork the repository under your account
3. Clone the repository to your local machine

		$ git clone https://github.com/<username>/Lux-1.git

4. Enter Username/password
5. Assign upstream to the original 

		$ git remote add upstream https://github.com/PhiladelphiaGameLab/Lux.git
		$ git fetch upstream
		
6. Push commits to local repository

		$ git add <file1> <file2>
		$ git commit -m "message about changes"

7. Push commits to your fork

		$ git push orgin master
		
8. When needed you can pull in and update your repository with 

		$ git fetch upstream
		$ git merge upstream/master
		
9. Create pull request on github when your section is complete
10. Changes will be confirmed and merged on github


# Sections:	

## Location Based HashMap -> Task 1 **(5 days using std Map)**
*Mike?*

* Build a HashMap that can map location to general Bucket for BGT
* Within the HashMap, a second query can get you the LBHM for the BGT
	* Returns a linked list of sockets in the adjacent areas
* Passing in a socket will erase the previous location of that socket and add new one
* Delete a single socket without adding a new one when one disconnects
* Non-Blocking, need to be able to read many and not block unless writing
* Needs to be stored in shared memory

## Main Message Passing Server (MMPS) -> Task 1 **(2 Days using assumed)**
*Jake*

* user connects, verify token/IP from CTT
	* Access Database and find corresponding Client location
* Read from initial database the location and the map section
* Pass location to BGT HashMap to find corresponding thread
* Send Thread Socket location to client
	* Client connects to the socket



			int main(int argc, char *argv[]){
				Socket socket(port);
				socket.init();
				
				for(i in #BGT){
					read_Next_Location_Area
					pthread_create(&BGT);
					map(BGT_Location, BGT_Port)
				}
				forever(){
					socket.recieve(cli_addr);
					verify(cli_token);
					location = cli_location;
					port = map_Query(cli_location);
					socket.send(cli_addr, port);
				}
			}


## Battle Ground Thread (BGT) -> Task 2 **(7 days)**

* set up area database by cloning base (if needed)
* Receive user message
* verify token
* verify location = location
	* if not, send them a reconnect warning
* pass player data into parsing location and updating socket location
	* update in HashMap location with new cli_socket
	* delete that clients old HashMap Location?
* Pipe Messages into the Shout Queue
* Pipe Messages into the Broadcast Queue that are relevant to everyone
* update objects in db
* Pipe Messages into analytics Queue

## Shout Thread -> Task 3 **(2 days)**
*Jake*

* Read messages from Shout Queue
* Check message location
* find sockets from relevant buckets in HashMap Location
* Send message to everyone in HML area 
	* Convert to string first

## Broadcast Thread -> Task 3 **(2 days)**
*Jake*

* Read Messages from Broadcast Queue
* Send Message to everyone in the HashMap Location
	* Convert to string first

## Chat Server -> Task 4 **(10 days)**

* Graph Database
* Main thread stores Sockets
* requests to add friends/groups/ect
* Messages to HashMap sockets or friends 
* Send Messages to broadcast and shout threads like above 


## AuthO Process with Rest API -> Task 4 **(6 days)**

* php accessing a mysql database with named pipe for c++ to read from
* php generates user token for session after client is verified
* client reads the returned user token and uses it to connect to the MMPS 
* c++ process to read from pipe and write to shared mem Hash Table [token, IP, Name]
	* Client Token Table (CTT)	
* Client sign-ups handled in same API
* Basic Sign-up form avaliable but connects to server via API 

## Fail recovery Process 
	
* Process to relaunch failed threads
* Process to make sure that there is no interupt to gameplay on updates	
* Ensures reliablity across all other aspects

Download and Patch Server
Admin Server with stuff
	* Auto-loading of maps and data
Analytics Server
