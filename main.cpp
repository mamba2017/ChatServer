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

#define BUFFER_LENGTH		1024
#define EPOLL_SIZE			1024

int main(int argc,char* argv[]) {
    ChatServer server;
    server.run();
//     if (argc < 2) {
// 		printf("Parm Error\n");
// 		return -1;
// 	}
//     int keepalive = 1;  
// 	int port = atoi(argv[1]);
//    printf("创建套接字\n");
// 	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if(setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepalive, sizeof (keepalive)) < 0){           
//             perror("fail to set SO_KEEPALIVE");
//             exit(-1);      
//     }
// 	struct sockaddr_in addr;
// 	memset(&addr, 0, sizeof(struct sockaddr_in));
// 	addr.sin_family = AF_INET;
// 	addr.sin_port = htons(port);
// 	addr.sin_addr.s_addr = INADDR_ANY;
//      printf("绑定套接字\n");
// 	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
// 		perror("bind");
// 		return 2;
// 	}
//   printf("监听套接字\n");
// 	if (listen(sockfd, 5) < 0) {
// 		perror("listen");
// 		return 3;
// 	}
// printf("创建一个epoll\n");
//     // 创建一个epoll
//     int epfd = epoll_create(1);
//     struct epoll_event events[EPOLL_SIZE] = {0};
// printf("储存epoll监听的IO事件\n");
//     // 储存epoll监听的IO事件
//     struct epoll_event ev;
//     ev.events = EPOLLIN;
//     ev.data.fd = sockfd;
//     printf("把socket交给epoll去管理\n");
//     // 把socket交给epoll去管理
//     epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

//     while (1) {
//         // epfd: 指定哪一个epoll
//         // events: 指定监听事件的容器
//         // EPOLL_SIZE: 数组大小
//         // -1: 表示只要没有IO事件就不去处理，0表示有时间就去处理
//         // 返回处理的IO事件的个数
//         int nready = epoll_wait(epfd, events, EPOLL_SIZE, -1);
//         if (nready == -1) {
//             continue;
//         }

//         // 依次处理IO事件
//         // events容器中会储存两种fd，一种是sockfd，一种是clientfd
//         int i = 0;
//         for (i = 0; i < nready; i++) {
//             // 触发IO事件的是sockfd，要进行accept处理
//             if (events[i].data.fd == sockfd) {
//                 struct sockaddr_in client_addr;
// 				memset(&client_addr, 0, sizeof(struct sockaddr_in));
// 				socklen_t client_len = sizeof(client_addr);

//                 // 建立连接之后得到新的clientfd
// 				int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
            
//                 // 确定事件的触发方式
//                 // 水平触发（有数据就触发，可能会触发多次）和边沿触发（检测到状态的改变才会触发）
//                 // 这里使用边沿触发
// 				ev.events = EPOLLIN | EPOLLET;
// 				ev.data.fd = clientfd;
//                 // clientfd交给epoll管理
// 				epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev);
//             } else {
//                 // 触发的是clientfd，要进行读写操作
//                 int clientfd = events[i].data.fd;

// 				char buffer[BUFFER_LENGTH] = { 0 };
// 				int len = recv(clientfd, buffer, BUFFER_LENGTH, 0);
// 				if (len < 0) {
// 					close(clientfd);
// 					ev.events = EPOLLIN | EPOLLET;
// 					ev.data.fd = clientfd;
//                     // 及时清除IO
// 					epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, &ev);
// 				}
// 				else if (len == 0) {
//                     printf("客户端断开%d: %s, %d byte(s)\n", clientfd,buffer, len);
// 					close(clientfd);
// 					ev.events = EPOLLIN | EPOLLET;
// 					ev.data.fd = clientfd;
//                     // 及时清除IO
// 					epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, &ev);
// 				}
// 				else {
// 					printf("Recv%d: %s, %d byte(s)\n", clientfd,buffer, len);
//                     write(clientfd,buffer,len);
// 				}
//             }
//         }

//     }
    return 0;
}

