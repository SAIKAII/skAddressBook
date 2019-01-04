#ifndef ADDRESSBOOK_INCLUDE_ONLINEDBOP_H_
#define ADDRESSBOOK_INCLUDE_ONLINEDBOP_H_

#include "global_config.h"
#include "online.h"
#include <mysql/mysql.h>
#include <string>
#include <memory>
#include <vector>

class OnlineDBOP{
public:
  static OnlineDBOP *get_instance(){
    static OnlineDBOP onlinedbop;
    return &onlinedbop;
  }
  void init(const int port = 40000);
  std::shared_ptr<std::vector<Online>> query_onlines(const std::string &sql);
  ~OnlineDBOP();

private:
  OnlineDBOP();
  bool update_tbl_online(const std::string &);

  MYSQL *conn_;
};

#endif
