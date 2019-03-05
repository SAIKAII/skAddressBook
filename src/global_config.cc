#include "../include/global_config.h"
#include "../include/contact_databaseop.h"
#include "../include/contact.h"
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>
#include <vector>

#include <iostream>

void GlobalConfig::set_name(const std::string &ip){
  // ...log通过IP地址从“联系人”表中获取客户端信息
  std::string sql = "select id, name, sex, address, ip "
                    "from contacts "
                    "where ip = '" + ip + "';";
  ContactDatabaseOP *dbop = ContactDatabaseOP::get_instance();
  std::shared_ptr<std::vector<Contact>> contact_v = dbop->query_contacts(sql);
  if(contact_v->size() > 0)
    name_ = contact_v->front().get_name();
  else
    exit(1);
}
