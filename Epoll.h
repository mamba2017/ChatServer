#include <sys/epoll.h>
#include <string>
 #include <iostream>
 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <list>
#include <errno.h>
#include <fcntl.h>
#include <vector>
#include <sys/socket.h>
#include "ChatSocket.h"
#include "protocol.h"
 typedef unsigned short uint16;
 #define EPOLL_SIZE			1024
 #define BUFFER_LENGT		1024
 using namespace std;

class Epoll
{
public:
    Epoll(int sockfd);
    void run();
 private:
    int m_sockfd;
};