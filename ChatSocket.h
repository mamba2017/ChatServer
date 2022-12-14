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
 using namespace std;
 typedef unsigned short uint16;
class ChatSocket
{
public:
    ChatSocket(int sockfd);
    void offLine(int m_sockfd);
    int    m_sockfd;
    string m_userName;
    static void handler(int sockfd,PDU *pdu);
private:
    
   
   
};

