/********************************************************
*
* CS 410
* Encrypted Instant Messenger
* Team 7, #2scoops
*
* File: client.cpp
*
* Set up communication for the client with the server.
*
* Compile: g++ client.cpp -o client
*
* Run: ./client 8080
*
********************************************************/

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>

using namespace std;

#define BUFSIZE 1024

void sendlogin(string username, string password, int server);

int main(int argc, char **argv)
{
    // setup default arguments
    int option;
    int port = 3000;
    string host = "localhost";

    // process command line options using getopt()
    // see "man 3 getopt"
    while ((option = getopt(argc,argv,"h:p:")) != -1) {
        switch (option) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'h':
                host = optarg;
                break;
            default:
                cout << "client [-s IP address] [-p port]" << endl;
                exit(EXIT_FAILURE);
        }
    }

    // use DNS to get IP address
    struct hostent *hostEntry;
    hostEntry = gethostbyname(host.c_str());
    if (!hostEntry) {
        cout << "No such host name: " << host << endl;
        exit(-1);
    }

      // setup socket address structure
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    memcpy(&server_addr.sin_addr, hostEntry->h_addr_list[0], hostEntry->h_length);

      // create socket
    int server = socket(PF_INET,SOCK_STREAM,0);
    if (server < 0) {
        perror("socket");
        exit(-1);
    }

      // connect to server
    if (connect(server,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("connect");
        exit(-1);
    }

    string one, two;

    cout << "Enter Username: ";
    cin >> one;
    cout <<"Enter Password: ";
    cin >> two;
    sendlogin(one, two, server);
/*    // allocate buffer
    int buflen = 1024;
    char* buf = new char[buflen+1];

    // read a line from standard input
    string line;
    while (getline(cin,line)) {

        // write the data to the server
        send(server, line.c_str(), line.length(), 0);

        // read the response
        memset(buf,0,buflen);
        recv(server,buf,buflen,0);
        
        // print the response
        cout << buf << endl;
    }*/

    // Close socket
    close(server);
}

void sendlogin(string username, string password, int server){
    char* usernameBuff = new char[BUFSIZE+1];
    send(server, username.c_str(), username.length(), 0);
    memset(usernameBuff,0,BUFSIZE);
    recv(server,usernameBuff,BUFSIZE,0);

    char* passwordBuff = new char[BUFSIZE+1];
    send(server, password.c_str(), password.length(), 0);
    memset(passwordBuff,0,BUFSIZE);
    recv(server,passwordBuff,BUFSIZE,0);

}