#ifndef OPENDB_H
#define OPENDB_H
#include <mysql.h>
#include<string.h>
#include <string>
#include <iostream>
#include <vector>
class OpenDB
{

public:
    explicit OpenDB();
    static OpenDB& getInstance();
    void init();
    bool UserRegister(const std::string &name, const std::string &pwd);
    bool Userlogin(const std::string &name, const std::string &pwd);
    void Userlogout(const std::string &name);
    std::vector<std::string> SearchOnlineUser();
    int SearchUser(const char* name);
    int AddFriend(const char* friendName,const char* currentUser);
    bool MakeFriendship(const char* friendName,const char* currentUser);
    std::vector<std::string> FreshFriend(const char* Name);
    ~OpenDB();

private:
    MYSQL *conn_ptr;   
};

#endif // OPENDB_H
