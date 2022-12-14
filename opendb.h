#ifndef OPENDB_H
#define OPENDB_H
#include <mysql.h>
#include <string>
#include <iostream>

class OpenDB
{

public:
    explicit OpenDB(QObject *parent = nullptr);
    static OpenDB& getInstance();
    void init();
    bool UserRegister(const char* name,const char* pwd);
    bool Userlogin(const char* name,const char* pwd);
    void Userlogout(const char* name);
    QStringList SearchOnlineUser();
    int SearchUser(const char* name);
    int AddFriend(const char* friendName,const char* currentUser);
    bool MakeFriendship(const char* friendName,const char* currentUser);
    QStringList FreshFriend(const char* Name);
    ~OpenDB();

private:
    QSqlDatabase m_db;
};

#endif // OPENDB_H
