#ifndef ADDRESSBOOK_INCLUDE_COMMUNICATION_H_
#define ADDRESSBOOK_INCLUDE_COMMUNICATION_H_

#include "onlinedbop.h"
#include <memory>

class Communication{
public:
  Communication();
  void start();

private:
  void print_all_onlines(const OnlineDBOP *);
  std::shared_ptr<Message> create_msg();
  void comm_with_all();
  void comm_with_one();

  std::shared_ptr<std::vector<Online>> onlines_;
};

#endif
