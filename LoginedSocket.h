#include <iostream>
#include<list>
#include "protocol.h"
#include <sys/socket.h>
class LoginedUserSock
{
public:
   LoginedUserSock();
   LoginedUserSock(int s,std::string n);
   static  LoginedUserSock& getInstance();
   void broadcast(PDU *pdu);

   int   socketFd;
   std::string name;
   std::list<LoginedUserSock*> lus;
};
