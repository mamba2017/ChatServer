#include <iostream>
#include<list>
class LoginedUserSock
{
public:
LoginedUserSock();
LoginedUserSock(int s,std::string n);
static  LoginedUserSock& getInstace();

   int         socketFd;
   std::string name;
   std::list<LoginedUserSock*> lus;
};
