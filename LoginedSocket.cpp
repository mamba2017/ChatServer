#include "LoginedSocket.h"
#include <string.h>
#include <time.h> 
#include <stdio.h>
#include <unistd.h>
LoginedUserSock::LoginedUserSock(){}
LoginedUserSock::LoginedUserSock(int s,std::string n):socketFd(s),name(n){}

void LoginedUserSock::broadcast(PDU * pdu)
{
    char Name[32] = {'\0'};
    memcpy(Name,pdu->caData,32);
    char msg[pdu->uiMsgLen];
    memcpy(msg,(char *)pdu->msg,pdu->uiMsgLen);
    time_t t = time(0);
    char tmptime[32]; 
    strftime(tmptime,sizeof(tmptime),"%Y/%m/%d %X",localtime(&t));

    PDU *broadcastPdu = mkPDU(pdu->uiMsgLen);
    broadcastPdu->uiMsgType = ENUM_MSG_TYPE_MSG_BROADCAST_REQUEST;
    memcpy(broadcastPdu->caData,tmptime,strlen(tmptime));
    memcpy(broadcastPdu->caData+32,Name,32);
    memcpy(broadcastPdu->msg,msg,pdu->uiMsgLen);
    std::list<LoginedUserSock*>::iterator iter = lus.begin();
    for(;iter!= lus.end();++iter){
           write((*iter)->socketFd,broadcastPdu,broadcastPdu->uiPDUlen);
    }
    free(broadcastPdu);
    broadcastPdu = nullptr;
    std::cout<<tmptime <<" sender:"<<Name<<":"<<msg<<std::endl;;
}



LoginedUserSock &LoginedUserSock::getInstance()
{
    static LoginedUserSock s;
    return s;
}
