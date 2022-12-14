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
#include <sys/epoll.h>
#include "ChatServer.h"
#include "opendb.h"

#define BUFFER_LENGTH		1024
#define EPOLL_SIZE			1024

int main(int argc,char* argv[]) {
    OpenDB::getInstance().init();
    ChatServer server;
    server.run();
    return 0;
}

