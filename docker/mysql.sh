
#!/bin/bash

user="root"  #用变量来存储用户
DB="xiewei"   #数据库为class
TB="users" #需要建立的表是student

mysql -u$user -p123456 <<EOF  #前面实现了免密码登录，这里就不需要写密码了
drop database $DB;   #如果数据库存在，先删除，方便脚本重复执行
create database $DB; #建立数据库
use $DB;  

CREATE TABLE users (
    id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL UNIQUE,
    phone VARCHAR(11) NOT NULL,
    password VARCHAR(255) NOT NULL, 
    email VARCHAR(255),
    status INT  default 0  # 设置默认值 0 offline
)ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE friends (
    id INT,
    friends_id INT
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
EOF