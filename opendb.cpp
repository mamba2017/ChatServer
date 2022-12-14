#include "opendb.h"
#include <sys/timeb.h>
#include <string>
OpenDB::OpenDB()
{
	conn_ptr = mysql_init(NULL);  //初始化MYSQL句柄
 
	if(!conn_ptr)   //若初始化句柄失败
	{
		printf("connect mysql failed");
	}
}

OpenDB &OpenDB::getInstance()
{
    static OpenDB db;
    return db;
}

void OpenDB::init()
{
   	/*尝试与mysql数据库连接*/
	if(!mysql_real_connect(conn_ptr,"192.168.211.141","root"
		,"123456","chatServer",0,NULL,0))
	{
		printf("failed to coonect mysql:%s\n",mysql_error(conn_ptr));
	}else
	{
		printf("db init success...........\n");
    //     std::string query_str = "select * from users";
    //     int rc = mysql_real_query(conn_ptr, query_str.c_str(), query_str.size());
    // if (0 != rc) {
    //     printf("mysql_real_query(): %s\n", mysql_error(conn_ptr));
     
    // }
    // MYSQL_RES *res = mysql_store_result(conn_ptr);
    // if (NULL == res) {
    //      printf("mysql_restore_result(): %s\n", mysql_error(conn_ptr));
    // }
    // int rows = mysql_num_rows(res);
    // int fields = mysql_num_fields(res);
    // MYSQL_ROW row;
    // int i;
    // while ((row = mysql_fetch_row(res))) {
    //     for (i = 0; i < fields; i++) {
    //         printf("%s\t", row[i]);
    //     }
    //     printf("\n");
    // }
    // mysql_free_result(res);
	}
}

bool OpenDB::UserRegister(const std::string &name, const std::string &pwd)
{   std::cout <<"User Register:"<<name<<std::endl;
    // timeb t;
    // long int tt = static_cast<long int>(t.time);
    // std::string ti =  std::to_string(tt);
    char inert_str[255] = {"0/"};
    sprintf(inert_str,"insert into users(name,phone,password,email) \
    values ('%s', '18855626285', '%s','13241@qq.com')",name.c_str(),pwd.c_str());
    int rc = mysql_real_query(conn_ptr, inert_str, strlen(inert_str));
    if(rc != 0){
        std::cout << "Register failed";
        return false;
    }
    return true;
}

bool OpenDB::Userlogin(const std::string &name, const std::string &pwd)
{
    std::cout <<"User Login:"<<name<<std::endl;
     if(name.empty() || name.empty()) return false;
      std::string select_str ="select * from users where name = '"+name+"' and password = '"+pwd+"' and status = 0";
      int rc = mysql_real_query(conn_ptr, select_str.c_str(), select_str.size());
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(conn_ptr));
        return false;
    }
    MYSQL_RES *res = mysql_store_result(conn_ptr);
    if (NULL == res) {
         printf("mysql_restore_result(): %s\n", mysql_error(conn_ptr));
         return false;
    }
    int rows = mysql_num_rows(res);
    if(rows <0){
        return false;
    }
    mysql_free_result(res);
    std::string update_str = "UPDATE users SET status = 1 WHERE name = '"+name+"'";
    rc = mysql_real_query(conn_ptr, update_str.c_str(), update_str.size());
    if(rc != 0){
        std::cout << "Update failed";
        return false;
    }


    return true;
}

void OpenDB::Userlogout(const std::string &name)
{
    
   std::string update_str = "UPDATE users SET status = 0 WHERE name = '"+name+"'";
    // std::cout << "sql:"<<update_str;
    int rc = mysql_real_query(conn_ptr, update_str.c_str(), update_str.size());
    if(rc != 0){
        std::cout << "offline failed in db";
    }
}

std::vector<std::string> OpenDB::SearchOnlineUser()
{   
    std::vector<std::string> onlineList;
    std::string select_str ="select * from users where status = 1";
    int rc = mysql_real_query(conn_ptr, select_str.c_str(), select_str.size());
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(conn_ptr));
    }
    MYSQL_RES *res = mysql_store_result(conn_ptr);
    if (NULL == res) {
         printf("mysql_restore_result(): %s\n", mysql_error(conn_ptr));
    }
    int rows = mysql_num_rows(res);
    int fields = mysql_num_fields(res);
    MYSQL_ROW row;
    int i;
    while ((row = mysql_fetch_row(res))) {
       onlineList.push_back(row[1]);
    }
    mysql_free_result(res);

   return onlineList;
}

int OpenDB::SearchUser(const char *name)
{
    // if(name == nullptr){
    //     return -1; //用户不存在
    // }
    // QString reg = QString("select status from userInfo where  name = '%1'").arg(name);
    // QSqlQuery query;
    // query.exec(reg);
    // if(query.next()){
    //    return query.value(0).toInt();
    // }else{
    //     return -1; //用户不存在
    // }
    return 0;
}

int OpenDB::AddFriend(const char *friendName, const char *currentUser)
{
    // if(friendName == nullptr || currentUser == nullptr){
    //     return -1;//发生错误
    // }

    // if(SearchUser(friendName) == -1){
    //     return -1; //用户不存在
    // }

    // QString reg = QString("select * from friendInfo where (id = (select id from userInfo where name = '%1') and friendId = (select id from userInfo where name = '%2'))"
    //         "or(id = (select id from userInfo where name = '%3') and friendId = (select id from userInfo where name = '%4'))").arg(currentUser).arg(friendName)
    //         .arg(friendName).arg(currentUser);
    // QSqlQuery query;
    // qDebug()<<reg;
    // query.exec(reg);
    // if (query.next()){
    //     qDebug()<<"已经是好友关系";
    //     return 2;   //已经是好友关系
    // }else{
    //     QString reg = QString("select status from userInfo where name = '%1'").arg(friendName);
    //     QSqlQuery query1;
    //     qDebug()<<reg;
    //     query1.exec(reg);

    //     if(query1.next()){

    //         if(query1.value(0).toInt() == 1){
    //                   qDebug()<<"在线 status"<<query1.value(0).toInt();
    //             return 1;
    //         }else{
    //                   qDebug()<<"离线 status"<<query1.value(0).toInt();
    //             return 0; // 离线
    //         }

    //     }
    //     return -1;
    // }
    return 0;
}

bool OpenDB::MakeFriendship(const char *friendName, const char *currentUser)
{
    // int friendId;
    // int currentId;
    // qDebug()<<currentUser<<"添加"<<friendName;
    // QString reg = QString("select id from userInfo where name = '%1'").arg(friendName);

    // QSqlQuery search;
    // search.exec(reg);
    // if(search.next()){
    //     friendId = search.value(0).toInt();
    // }else{
    //     return false;
    // }
    // QString reg2 = QString("select id from userInfo where name = '%1'").arg(currentUser);

    // QSqlQuery search2;
    // search2.exec(reg2);
    // if(search2.next()){
    //     currentId = search2.value(0).toInt();
    // }else{
    //     return false;
    // }
    // qDebug()<<currentUser<<currentId<<"添加"<<friendName<<friendId;
    // QString reg3 = QString("insert into friendInfo(id,friendid) values(%1,%2),(%2,%1)").arg(friendId).arg(currentId);
    // qDebug()<<reg3;
    // QSqlQuery add;
    // return  add.exec(reg3);
    return true;
}

std::vector<std::string> OpenDB::FreshFriend(const char *Name)
{
    // QStringList list;
    // list.clear();

    // QString reg = QString("select friendid from friendInfo where id = (select id from userInfo where name = '%1')").arg(Name);
    // qDebug()<<reg;
    // QSqlQuery sql;
    // sql.exec(reg);
    // QList<int> friendid;
    // while(sql.next()){
    //     friendid.append(sql.value(0).toInt());
    // }
    // QList<int>::iterator iter = friendid.begin();
    // for(;iter != friendid.end();++iter){
    //     QString reg1 = QString("select name from userInfo where id = %1").arg(*iter);
    //     qDebug()<<reg1;
    //     QSqlQuery sql1;
    //     sql1.exec(reg1);
    //     if(sql1.next()){
    //         list.append(sql1.value(0).toString());
    //     }
    // }
    // return list;
    std::vector<std::string> p;
    return p;
}

OpenDB::~OpenDB()
{
    mysql_close(conn_ptr);
}
