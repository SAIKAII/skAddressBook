#include "../include/addressbook.h"
#include "../include/contact_databaseop.h"
#include <iostream>
#include <iomanip>

AddressBook::AddressBook(){
  // ...log通讯录初始化开始
  std::string sql = "select id, name, sex, address, ip"
                     "from contacts";
  ContactDatabaseOP *dbop = ContactDatabaseOP::get_instance();
  contacts_v_ = dbop->query_contacts(sql);
  // ...log通讯录初始化完成
}

void AddressBook::print_info(){
  std::cout << std::ios::left << std::setw(5) << "序号" << std::setw(10) << "姓名"
  << std::setw(4) << "性别" << std::setw(20) << "地址" << std::setw(17) << "IP地址" << std::endl;
  int index = 0;
  for(auto contact : (*contacts_v_)){
    std::cout << std::ios::left << std::setw(5) << ++index;
    contact.print_info();
  }
}

bool AddressBook::insert_contact(const Contact &contact){
  std::string sql_insert = "insert into contacts(name, sex, address, ip)"
                     "values ('"
                     + contact.get_name() + "', '"
                     + contact.get_sex() + "', '"
                     + contact.get_address() + "', '"
                     + contact.get_ip() + "');";
  ContactDatabaseOP *dbop = ContactDatabaseOP::get_instance();
  if(!dbop->update_tbl_contact(sql_insert)){
    // ...log插入联系人失败
    return false;
  }
  // ...log插入联系人成功
  // 查找刚插入的联系人id，并插入vector
  std::string sql_query = "select id, name, sex, address, ip"
                     "from contacts"
                     "where name = '" + contact.get_name() + "' and "
                            "sex = '" + contact.get_sex() + "' and "
                            "address = '" + contact.get_address() + "' and "
                            "ip = '" + contact.get_ip() +"';";
  Contact c = dbop->query_contacts(sql_query)->front();
  contacts_v_->push_back(c);
  // ...log成功插入联系人到内存
  return true;
}

bool AddressBook::delete_contact(int index){
  // 这里的index从1开始，所以要减1
  int contact_id = (*contacts_v_)[index-1].get_id();
  std::string sql = "delete from contacts where id = " + std::to_string(contact_id);
  ContactDatabaseOP *dbop = ContactDatabaseOP::get_instance();
  if(!dbop->update_tbl_contact(sql)){
    // ...log删除联系人失败
    return false;
  }
  // ...log删除联系人成功
  contacts_v_->erase(contacts_v_->begin()+index-1);
  // ...log内存中联系人删除成功
  return true;
}

void AddressBook::search_by_name(const std::string &name){
  std::string sql = "select id, name, sex, address, ip"
                    "from contacts"
                    "where name like '%" + name + "%';";
  ContactDatabaseOP *dbop = ContactDatabaseOP::get_instance();
  contacts_v_ = dbop->query_contacts(sql);
  // ...log以名字查找成功
  print_info();
}

void AddressBook::search_by_ip(const std::string &ip){
  std::string sql = "select id, name, sex, address, ip"
                    "from contacts"
                    "where ip like '%" + ip + "%';";
  ContactDatabaseOP *dbop = ContactDatabaseOP::get_instance();
  contacts_v_ = dbop->query_contacts(sql);
  // ...log以ip查找成功
  print_info();
}
