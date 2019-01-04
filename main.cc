#include "include/addressbook.h"
#include <string>
#include <iostream>

void print_usage(){
  std::cout << "1、显示联系人" << std::endl;
  std::cout << "2、插入联系人" << std::endl;
  std::cout << "3、删除联系人" << std::endl;
  std::cout << "4、查找联系人" << std::endl;
  std::cout << "5、与线上人联系" << std::endl;
  std::cout << "0、退出系统" << std::endl;
}

Contact *input_info(){
  std::string name, sex, address, ip;
  std::cout << "请按序输入姓名、性别、住址、IP地址：";
  std::cin >> name >> sex >> address >> ip;
  return new Contact(name, sex, address, ip);
}

void search_usage(){
  std::cout << "可以按照名字或者IP查询联系人，请输入想查询的方式" << std::endl;
  std::cout << "1、按照名字查询" << std::endl;
  std::cout << "2、按照IP查询" << std::endl;
  std::cout << "3、查询所有联系人" << std::endl;
  std::cout << "0、退出查询" << std::endl;
}

int main(){
  // ...log main函数开始
  AddressBook addressbook;
  std::cout << "----------欢迎进入通讯录----------" << std::endl;
  int flag = 1;
  while(true){
    print_usage();
    std::cout << "请输入序号：";
    std::cin >> flag;
    if(1 == flag){
      // ...log显示数据
      addressbook.print_info();
    }
    else if(2 == flag){
      // ...log插入联系人
      Contact *c_ptr = input_info();
      addressbook.insert_contact(c_ptr);
      delete c_ptr;
    }
    else if(3 == flag){
      // ...log删除联系人
      int index = 0;
      std::cout << "请输入要删除的联系人序号：";
      std::cin >> index;
      if(!addressbook.delete_contact(index)){
        std::cout << "删除失败，也许是序号错了。" << std::endl;
      }else{
        std::cout << "删除成功！" << std::endl;
      }
    }else if(4 == flag){
      int method = 0;
      search_usage();
      std::cin >> method;
      if(1 == method){
        std::string name;
        std::cout << "请输入想查询联系人名字：";
        std::cin >> name;
        addressbook.search_by_name(name);
      }else if(2 == method){
        std::string ip;
        std::cout << "请输入想查询联系人IP：";
        std::cin >> ip;
        addressbook.search_by_ip(ip);
      }else if(3 == method){
        addressbook.search_all();
      }else{
        std::cout << "此次查询终止" << std::endl;
      }
    }else if(5 == flag){
      // ...log开始与线上人联系
      Communication communication;
      communication.start();
      // ...log与线上人联系结束
    }else if(0 == flag){
      // ...log正常退出程序
      break;
    }else{
      std::cout << "无效的输入！" << std::endl;
    }
  }
  std::cout << "----------成功退出系统----------" << std::endl;
}
