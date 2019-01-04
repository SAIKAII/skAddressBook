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

GlobalConfig::GlobalConfig(){
  char hname[128];
  struct hostent *hent;

  // ...log获取本机IP
  gethostname(hname, sizeof(hname));
  hent = gethostbyname(hname);
  std::string ip = inet_ntoa(*(in_addr*)hent->h_addr_list[0]);
  // ...log获取本机IP成功

  // ...log通过IP地址从“联系人”表中获取客户端信息
  std::string sql = "select id, name, sex, address, ip "
                    "from contacts "
                    "where ip = '" + ip + "';";
  ContactDatabaseOP *dbop = ContactDatabaseOP::get_instance();
  std::shared_ptr<std::vector<Contact>> contact_v = dbop->query_contacts(sql);
  name_ = contact_v->front().get_name();
  // ...log获取本机联系人姓名成功
}
