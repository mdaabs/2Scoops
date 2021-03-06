/*
*Compile:
*Client
*g++ Client.cpp -o Client
*./Client localhost <port number>
*/

#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
void *parseData(void *clsk){
	cout<<"threading"<<endl;
	char messageBuffer[256];
	int clientSocket=*((int*)clsk);
	while(1){
	memset(messageBuffer,0,sizeof(messageBuffer));
	//cout<<"waiting on message"<<endl;
	read(clientSocket, messageBuffer,256);
	//cout<<"recieving message"<<endl;
	string decipheredMessage (messageBuffer);
	//std::string encryptedMessage (messageBuffer);
	//std::string decipheredMessage;
	//decipheredMessage=decryptIncomingMessage(encryptedMessage);
	cout<<decipheredMessage<<endl;
	}

}
int main (int argc, char* argv[])
{
    int listenFd, portNo;
    bool loop = false;
    struct sockaddr_in svrAdd;
    struct hostent *server;
    
    if(argc < 3)
    {
        cerr<<"Syntax : ./client <host name> <port>"<<endl;
        return 0;
    }
    
    portNo = atoi(argv[2]);
    
    if((portNo > 65535) || (portNo < 2000))
    {
        cerr<<"Please enter port number between 2000 - 65535"<<endl;
        return 0;
    }       
    
    //create client skt
    listenFd = socket(PF_INET, SOCK_STREAM, 0);
    
    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }
 server = gethostbyname(argv[1]);
    
    if(server == NULL)
    {
        cerr << "Host does not exist" << endl;
        return 0;
    }
       cout<<"address is: "<<&svrAdd<<endl;    
    bzero((char *) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;
    
    bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);
    
    svrAdd.sin_port = htons(portNo);
    
    int checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
   cout<<"address is: "<<&svrAdd<<endl;    

    if (checker < 0)
    {
        cerr << "Cannot connect!" << endl;
        return 0;
    }
	cout<<"about to thread"<<endl;
    	pthread_t thread;
	pthread_create(&thread, NULL, parseData, &listenFd);
    //send stuff to server
    for(;;)
    {
        char s[300];
        //cin.clear();
        //cin.ignore(256, '\n');
       // cout << "Enter stuff: ";
        bzero(s, 301);
        cin.getline(s, 300);
        
        write(listenFd, s, strlen(s));
        //bzero(s, 301);
	//cout<<"waiting on string"<<endl;
	//read(listenFd, s, strlen(s));
	//string str (s);
	//cout<<"received string"<<endl;
	//cout<<str<<endl;

    }
}


