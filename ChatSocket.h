#include <string>
 #include <iostream>
 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <protocol.h>

#include <list>

 using namespace std;
 typedef unsigned short uint16;

class ChatSocket
{
public:
   
    ChatSocket(int sockfd);
    static void offLine(int m_sockfd);
    static void login(const int &m_sockfd,const std::string &name);
    static void handler(int sockfd,PDU *pdu);
    static void printOline();
private:
   
};

