#ifndef USER_H
#define USER_H

#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
const int MAX=100;
#define Delim '|'

class User
{

     string username;
	//string password;
     bool online;
	public:
	User(string, bool);

};
User::User(string a, bool b){

	username=a;
	online=b;

} 



#endif // USER_H
