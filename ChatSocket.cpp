#include "ChatSocket.h"
#include "opendb.h"
#include "LoginedSocket.h"

ChatSocket::ChatSocket(int sockfd){

}

void ChatSocket::offLine(int delete_sockfd)
{
        std::string name;
        std::list<LoginedUserSock *>::iterator iter = LoginedUserSock::getInstace().lus.begin();
        for(;iter!=LoginedUserSock::getInstace().lus.end();iter++){
            if((*iter)->socketFd == delete_sockfd){
                name = (*iter)->name;
                break;
            }
        }
        LoginedUserSock::getInstace().lus.remove_if([&](LoginedUserSock *del){
                        return del->socketFd == delete_sockfd;
                    });
       
        OpenDB::getInstance().Userlogout(name);

        printOline();
}

void ChatSocket::login(const int &m_sockfd,const std::string &name)
{
    LoginedUserSock *login = new LoginedUserSock(m_sockfd,name);
    LoginedUserSock::getInstace().lus.push_back(login);
    printOline();
}

void ChatSocket::handler(int clientfd, PDU *pdu)
{
    switch (pdu->uiMsgType)
    {
    case ENUM_MSG_TYPE_REGIST_REQUEST:{
        /* code */
        char name[32] = {"0/"};
        char passwd[32] = {"0/"};
        memcpy(name,pdu->caData,32);
        memcpy(passwd,pdu->caData+32,32);
        PDU *pdu2 = mkPDU(0);
        if(OpenDB::getInstance().UserRegister(name,passwd)){
            pdu2->uiMsgType = ENUM_MSG_TYPE_REGIST_SUCCESS_RESPONSE;
        }else{
            pdu2->uiMsgType = ENUM_MSG_TYPE_REGIST_FAILED_RESPONSE;
        }
        write(clientfd,pdu2,pdu2->uiPDUlen);
        delete pdu2;
        pdu2 = nullptr;
        break;
        }
     case ENUM_MSG_TYPE_LOGIN_REQUEST:{
        /* code */
        char name[32] = {"0/"};
        char passwd[32] = {"0/"};
        memcpy(name,pdu->caData,32);
        memcpy(passwd,pdu->caData+32,32);
        PDU *pdu5 = mkPDU(0);
        if(OpenDB::getInstance().Userlogin(name,passwd)){
            pdu5->uiMsgType = ENUM_MSG_TYPE_LOGIN_SUCCESS_RESPONSE;
             login(clientfd,name);
        }else{
            pdu5->uiMsgType = ENUM_MSG_TYPE_LOGIN_FAILED_RESPONSE;
        }
         write(clientfd,pdu5,pdu5->uiPDUlen);
        delete pdu5;
        pdu5 = nullptr;
        break;
        }
     case ENUM_MSG_TYPE_ALL_ONLINE_REQUEST:{
        std::vector<std::string> ret = OpenDB::getInstance().SearchOnlineUser();
        uint uiMsgLen = ret.size()*32;  //每个名字占32字节；
        PDU *pdu7 = mkPDU(uiMsgLen);
        pdu7->uiMsgType = ENUM_MSG_TYPE_ALL_ONLINE_RESPONSE;
        for(int i = 0;i<ret.size();++i){
            memcpy((char *)(pdu7->msg)+(i*32),ret.at(i).c_str(),ret.at(i).size());
        }
        write(clientfd,pdu7,pdu7->uiPDUlen);
        free(pdu7);
        pdu7 = nullptr;
        break;
      }
     case ENUM_MSG_TYPE_SEARCH_USER_REQUEST:{
        int ret = OpenDB::getInstance().SearchUser(pdu->caData);
        PDU *pdu10 = mkPDU(0);
        pdu10->uiMsgType = ENUM_MSG_TYPE_SEARCH_USER_RESPONSE;
        // memcpy((char *)(pdu10->caData),QString("%1").arg(ret).toStdString().c_str(),32);
        write(clientfd,pdu10,pdu10->uiPDUlen);
        delete pdu10;
        pdu10 = nullptr;
        break;
     }
      case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST:
    {
    //     char friendName[32] = {'\0'};
    //     char currentUser[33] = {'\0'};
    //     memcpy(friendName,pdu->caData,32);
    //     memcpy(currentUser,pdu->caData+32,32);
    //     int ret = OpenDB::getInstance().AddFriend(friendName,currentUser);
    //     PDU *pdu11 = mkPDU(0);
    //     pdu11->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_RESPONSE;
    //     if(ret == -1){  // 用户不存在
    //         strcpy(pdu11->caData,"用户不存在");
    //         write((char *)pdu11,pdu11->uiPDUlen);
    //     }else if(ret == 0){  // 离线
    //         strcpy(pdu11->caData,"用户已离线");
    //         write((char *)pdu11,pdu11->uiPDUlen);
    //     }else if(ret == 1){  //转发请求
    //             MyTcpServer::getInstance().retransmission(friendName,pdu);
    //     }else if(ret == 2){
    //         strcpy(pdu11->caData,"用户已经是你的好友");
    //         write((char *)pdu11,pdu11->uiPDUlen);
    //     }
    //     free(pdu11);
    //     pdu11 = nullptr;
        break;
    }
    case ENUM_MSG_TYPE_MSG_BROADCAST_REQUEST:
    {
        // MyTcpServer::getInstance().broadcast(pdu);
        // break;
    }
    default:
        break;
    }
    
}

void ChatSocket::printOline()
{
    std::cout <<"pepoles online: ";
    if(LoginedUserSock::getInstace().lus.empty()){
        std::cout << " 0 "<<std::endl;
        return;
    }
    std::list<LoginedUserSock *>::iterator iter = LoginedUserSock::getInstace().lus.begin();
    for(;iter!=LoginedUserSock::getInstace().lus.end();iter++){
        if((*iter)->socketFd == LoginedUserSock::getInstace().lus.back()->socketFd){
            std::cout << (*iter)->name<< std::endl;
            break;
        }
        std::cout << (*iter)->name<< "->";
    }
}
