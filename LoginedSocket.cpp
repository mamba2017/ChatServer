#include "LoginedSocket.h"
LoginedUserSock::LoginedUserSock(){}
LoginedUserSock::LoginedUserSock(int s,std::string n):socketFd(s),name(n){}



LoginedUserSock &LoginedUserSock::getInstace()
{
    static LoginedUserSock s;
    return s;
}
