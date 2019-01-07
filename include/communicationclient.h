#ifndef ADDRESSBOOK_INCLUDE_COMMUNICATIONCLIENT_H_
#define ADDRESSBOOK_INCLUDE_COMMUNICATIONCLIENT_H_

#include "client_server.h"
#include "online.h"
#include "../include/message_packet_and_unpacking.h"
#include <memory>
#include <unistd.h>

class CommunicationClient : public ClientServer{
public:
  CommunicationClient(const Online &, std::shared_ptr<MessagePacket> &);
  void send_message();
  void recv_message();
  ~CommunicationClient(){}

private:
  std::shared_ptr<MessagePacket> msg_ptr_;
};

#endif
