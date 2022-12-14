#include <string>
 #include <iostream>
 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>

 using namespace std;
 typedef unsigned short uint16;
class ChatServer
{
public:
    ChatServer();

    int loadConfig();
    int run();
private:
    string m_strIP;
    uint16 m_usPort;

};

