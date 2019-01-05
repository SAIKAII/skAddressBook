#ifndef ADDRESSBOOK_INCLUDE_COMMUNICATIONCLIENT_H_
#define ADDRESSBOOK_INCLUDE_COMMUNICATIONCLIENT_H_

#include "online.h"
#include "../include/message_packet_and_unpacking.h"
#include <ctime>
#include <memory>
#include <unistd.h>

class CommunicationClient{
public:
  CommunicationClient(const Online &, std::shared_ptr<MessagePacket> &);
  void send_message();
  void recv_message();
  void set_time(){ start_time_ = std::time(nullptr); }
  std::time_t get_time(){ return start_time_; }
  ~CommunicationClient(){ close(sockfd_); }

private:
  int sockfd_;
  std::time_t start_time_;
  std::shared_ptr<MessagePacket> msg_ptr_;
};

#endif
