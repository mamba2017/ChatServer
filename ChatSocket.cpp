#include "ChatSocket.h"

ChatSocket::ChatSocket(int sockfd):m_sockfd(sockfd){}

void ChatSocket::offLine(int m_sockfd)
{


}

void ChatSocket::handler(int clientfd, PDU *pdu)
{
    printf("msgtype:%d\n",pdu->uiMsgType);
    switch (pdu->uiMsgType)
    {
    case ENUM_MSG_TYPE_REGIST_REQUEST:
        /* code */
        break;
     case ENUM_MSG_TYPE_LOGIN_REQUEST:
        /* code */
        break;
     case ENUM_MSG_TYPE_ALL_ONLINE_REQUEST:
        /* code */
        break;
     case ENUM_MSG_TYPE_SEARCH_USER_REQUEST:
        /* code */
        break;
    
    default:
        break;
    }

    printf("name:%s\n",pdu->caData);
    printf("passwd:%s\n",pdu->caData+32);
    char buffer[1024] = { 1 };
    write(clientfd,buffer,4);
}
