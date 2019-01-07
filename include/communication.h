#ifndef ADDRESSBOOK_INCLUDE_COMMUNICATION_H_
#define ADDRESSBOOK_INCLUDE_COMMUNICATION_H_

#include "onlinedbop.h"
#include "message.h"
#include "../include/message_packet_and_unpacking.h"
#include <memory>

class Communication{
public:
  void init();
  void start();
  ~Communication();

private:
  void print_all_onlines(OnlineDBOP *);
  std::shared_ptr<MessagePacket> create_msg();
  void comm_with_all();
  void comm_with_one();

  std::shared_ptr<std::vector<Online>> onlines_;
};

#endif
