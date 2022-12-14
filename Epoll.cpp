#include "Epoll.h"
 #define EPOLL_SIZE			1024
 #define BUFFER_LENGTsH		1024
Epoll::Epoll(int sockfd)
{
   m_sockfd = sockfd;
}

void Epoll::run()
{
    int epfd = epoll_create(1);
    struct epoll_event events[EPOLL_SIZE] = {0};
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = m_sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, m_sockfd, &ev);
    while (1) {
        int nready = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        if (nready == -1) {
            continue;
        }
        int i = 0;
        for (i = 0; i < nready; i++) {
            // 触发IO事件的是sockfd，要进行accept处理
            if (events[i].data.fd == m_sockfd) {
                struct sockaddr_in client_addr;
				memset(&client_addr, 0, sizeof(struct sockaddr_in));
				socklen_t client_len = sizeof(client_addr);

                // 建立连接之后得到新的clientfd
				int clientfd = accept(m_sockfd, (struct sockaddr*)&client_addr, &client_len);
            
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = clientfd;
                // clientfd交给epoll管理
				epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev);
            } else {
                // 触发的是clientfd，要进行读写操作
                int clientfd = events[i].data.fd;

				char buffer[1024] = { 0 };
				int len = recv(clientfd, buffer, 1024, 0);
				if (len < 0) {
					close(clientfd);
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = clientfd;
                    // 及时清除IO
					epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, &ev);
				}
				else if (len == 0) {
                    printf("客户端断开%d: %s, %d byte(s)\n", clientfd,buffer, len);
					close(clientfd);
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = clientfd;
                    // 及时清除IO
					epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, &ev);
				}
				else {
					printf("Recv%d: %s, %d byte(s)\n", clientfd,buffer, len);
                    uint uiPDULen = 0; //数据总长度
                    memcpy((char *)&uiPDULen, buffer, sizeof(uint));
                    printf("sizeof(PDU):%d\n",int(sizeof(PDU)));

                    PDU *pdu = mkPDU(uiPDULen-sizeof(PDU));
                    memcpy(pdu, buffer, uiPDULen);

                    ChatSocket::handler(clientfd,pdu);
				}
            }
        }
    }
}
