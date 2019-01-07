#include "../include/contact_databaseop.h"
#include <stdio.h>

static const char *kServer = "localhost";
static const char *kUser = "root";
static const char *kPassword = "123456";
static const char *kDB = "addressbook";
static const int kPort = 3306;

ContactDatabaseOP *ContactDatabaseOP::get_instance(){
  static ContactDatabaseOP dbop;
  return &dbop;
}

ContactDatabaseOP::ContactDatabaseOP(){
  // ... log初始化开始
  conn_ = mysql_init(NULL);
  if(NULL == conn_){
    // ...log数据库句柄初始化失败
    exit(1);
  }
  if(!mysql_real_connect(conn_, kServer, kUser, kPassword, kDB, 0, NULL, 0)){
    // ... log
    exit(1);
  }
  mysql_query(conn_, "set names 'utf8';");
  // ... log初始化完成
}

ContactDatabaseOP::~ContactDatabaseOP(){
  if(NULL != conn_){
    mysql_close(conn_);
    // ... log连接关闭成功
    return;
  }
  // ... log连接关闭失败
}

std::shared_ptr<std::vector<Contact>> ContactDatabaseOP::query_contacts(const std::string &sql){
  std::shared_ptr<std::vector<Contact>> contacts(new std::vector<Contact>());

  if(mysql_query(conn_, sql.c_str())){
    // ... log
    exit(1);
  }

  // 这里选用mysql_store_result是为了把负担放到客户端处，减少服务器负担
  // 否则可以使用mysql_use_result
  MYSQL_RES *res_ptr = mysql_store_result(conn_);
  MYSQL_ROW row;
  while((row = mysql_fetch_row(res_ptr)) > 0){
    contacts->emplace_back(atoi(row[0]), row[1], row[2], row[3], row[4]);
  }
  // 释放结果集的内存
  mysql_free_result(res_ptr);
  // ...log释放结果集的内存
  return contacts;
}

bool ContactDatabaseOP::update_tbl_contact(const std::string &sql){
  if(mysql_query(conn_, sql.c_str())){
    return false;
  }
  return true;
}
