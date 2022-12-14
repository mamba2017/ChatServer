#ifndef PROTOCOL_H
#define PROTOCOL_H
#define UNKNOW_ERROR "unknow error"
#define FRIEND_EXIST "friends exist"
typedef unsigned int uint;

struct PDU{
    uint uiPDUlen;  //总的协议单元大小
    uint uiMsgType; // 消息类型
    char caData[64];
    uint uiMsgLen;  //消息大小
    int msg[];  //实际消息
};
enum ENUM_MSG_TYPE  //消息类型
{
    ENUM_MSG_TYPE_MIN = 0,
    ENUM_MSG_TYPE_REGIST_REQUEST,
    ENUM_MSG_TYPE_REGIST_SUCCESS_RESPONSE,
    ENUM_MSG_TYPE_REGIST_FAILED_RESPONSE,

    ENUM_MSG_TYPE_LOGIN_REQUEST,
    ENUM_MSG_TYPE_LOGIN_SUCCESS_RESPONSE,
    ENUM_MSG_TYPE_LOGIN_FAILED_RESPONSE,

    ENUM_MSG_TYPE_ALL_ONLINE_REQUEST,   //在线用户请求
    ENUM_MSG_TYPE_ALL_ONLINE_RESPONSE,

    ENUM_MSG_TYPE_SEARCH_USER_REQUEST,   //搜索用户请求
    ENUM_MSG_TYPE_SEARCH_USER_RESPONSE,

    ENUM_MSG_TYPE_ADD_FRIEND_REQUEST,    //添加好友
    ENUM_MSG_TYPE_ADD_FRIEND_RESPONSE,
    ENUM_MSG_TYPE_ADD_FRIEND_AGREE,
    ENUM_MSG_TYPE_ADD_FRIEND_REFUSE,
    ENUM_MSG_TYPE_ADD_FRIEND_ERROR,

    ENUM_MSG_TYPE_FRESH_FRIEND_REQUEST,
    ENUM_MSG_TYPE_FRESH_FRIEND_RESPONSE,

    ENUM_MSG_TYPE_MSG_BROADCAST_REQUEST,
    ENUM_MSG_TYPE_MSG_BROADCAST_RESPONSE,
//    ENUM_MSG_TYPE_REQUEST,
//    ENUM_MSG_TYPE_RESPONSE,
    ENUM_MSG_TYPE_MAX = 0x00ffffff,
};
PDU* mkPDU(uint uiMsgLen);

#endif // PROTOCOL_H
