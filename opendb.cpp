#include "opendb.h"

OpenDB::OpenDB(QObject *parent) : QObject(parent)
{
 
}

OpenDB &OpenDB::getInstance()
{
    static OpenDB db;
    return db;
}

void OpenDB::init()
{
    m_db.setHostName("localhost");
    m_db.setDatabaseName("F:\\qtfile\\TcpServer\\cloud.db");
    if (m_db.open()){

        QSqlQuery query;
        query.exec("select * from userInfo");
        while(query.next()){
            QString data = QString("%1,%2").arg(query.value(0).toString()).arg(query.value(1).toString());
            qDebug()<<data;
        }
    }else{
        qDebug()<<"worng";
    }
}

bool OpenDB::UserRegister(const char *name, const char *pwd)
{   qDebug()<<"hello"<<name<<pwd;
    if(!name || !pwd) return false;
     QString reg = QString("insert into userInfo(name,pwd) values('%1','%2')").arg(name).arg(pwd);
    qDebug()<<reg;
    QSqlQuery query;
    bool ret = query.exec(reg);
    qDebug()<<ret;
    return ret;
}

bool OpenDB::Userlogin(const char *name, const char *pwd)
{
    qDebug()<<"login"<<name<<pwd;
     if(!name || !pwd) return false;
      QString reg = QString("select * from userInfo where name = '%1' and pwd = '%2' and status = 0").arg(name).arg(pwd);
     qDebug()<<reg;
     QSqlQuery query;
     bool ret = query.exec(reg);
     qDebug()<<ret;
     if(query.next()){ //找到记录就更新状态
         QString reg = QString("UPDATE userInfo SET status = 1 WHERE name = '%1'").arg(name);
         qDebug()<<reg;
         QSqlQuery update;

         return update.exec(reg);
     }else{
         return false;
     }

}

void OpenDB::Userlogout(const char *name)
{
    qDebug()<<"offline:"<<name;
    QString reg = QString("UPDATE userInfo SET status = 0 WHERE name = '%1'").arg(name);
    qDebug()<<reg;
    QSqlQuery offline;
    offline.exec(reg);
}

QStringList OpenDB::SearchOnlineUser()
{
   QStringList onlineList;
   onlineList.clear();
   QString reg = QString("select name from userInfo where  status = 1");
   qDebug()<<reg;
   QSqlQuery query;
   query.exec(reg);
   while(query.next()){
       qDebug()<<query.value(0).toString();
       onlineList.append(query.value(0).toString());
   }
   return onlineList;
}

int OpenDB::SearchUser(const char *name)
{
    if(name == nullptr){
        return -1; //用户不存在
    }
    QString reg = QString("select status from userInfo where  name = '%1'").arg(name);
    QSqlQuery query;
    query.exec(reg);
    if(query.next()){
       return query.value(0).toInt();
    }else{
        return -1; //用户不存在
    }
}

int OpenDB::AddFriend(const char *friendName, const char *currentUser)
{
    if(friendName == nullptr || currentUser == nullptr){
        return -1;//发生错误
    }

    if(SearchUser(friendName) == -1){
        return -1; //用户不存在
    }

    QString reg = QString("select * from friendInfo where (id = (select id from userInfo where name = '%1') and friendId = (select id from userInfo where name = '%2'))"
            "or(id = (select id from userInfo where name = '%3') and friendId = (select id from userInfo where name = '%4'))").arg(currentUser).arg(friendName)
            .arg(friendName).arg(currentUser);
    QSqlQuery query;
    qDebug()<<reg;
    query.exec(reg);
    if (query.next()){
        qDebug()<<"已经是好友关系";
        return 2;   //已经是好友关系
    }else{
        QString reg = QString("select status from userInfo where name = '%1'").arg(friendName);
        QSqlQuery query1;
        qDebug()<<reg;
        query1.exec(reg);

        if(query1.next()){

            if(query1.value(0).toInt() == 1){
                      qDebug()<<"在线 status"<<query1.value(0).toInt();
                return 1;
            }else{
                      qDebug()<<"离线 status"<<query1.value(0).toInt();
                return 0; // 离线
            }

        }
        return -1;
    }
}

bool OpenDB::MakeFriendship(const char *friendName, const char *currentUser)
{
    int friendId;
    int currentId;
    qDebug()<<currentUser<<"添加"<<friendName;
    QString reg = QString("select id from userInfo where name = '%1'").arg(friendName);

    QSqlQuery search;
    search.exec(reg);
    if(search.next()){
        friendId = search.value(0).toInt();
    }else{
        return false;
    }
    QString reg2 = QString("select id from userInfo where name = '%1'").arg(currentUser);

    QSqlQuery search2;
    search2.exec(reg2);
    if(search2.next()){
        currentId = search2.value(0).toInt();
    }else{
        return false;
    }
    qDebug()<<currentUser<<currentId<<"添加"<<friendName<<friendId;
    QString reg3 = QString("insert into friendInfo(id,friendid) values(%1,%2),(%2,%1)").arg(friendId).arg(currentId);
    qDebug()<<reg3;
    QSqlQuery add;
    return  add.exec(reg3);
}

QStringList OpenDB::FreshFriend(const char *Name)
{
    QStringList list;
    list.clear();

    QString reg = QString("select friendid from friendInfo where id = (select id from userInfo where name = '%1')").arg(Name);
    qDebug()<<reg;
    QSqlQuery sql;
    sql.exec(reg);
    QList<int> friendid;
    while(sql.next()){
        friendid.append(sql.value(0).toInt());
    }
    QList<int>::iterator iter = friendid.begin();
    for(;iter != friendid.end();++iter){
        QString reg1 = QString("select name from userInfo where id = %1").arg(*iter);
        qDebug()<<reg1;
        QSqlQuery sql1;
        sql1.exec(reg1);
        if(sql1.next()){
            list.append(sql1.value(0).toString());
        }
    }
    return list;
}

OpenDB::~OpenDB()
{
    m_db.close();
}
