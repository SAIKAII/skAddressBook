#ifndef ADDRESSBOOK_INCLUDE_MESSAGE_PACKET_AND_UNPACKING_H_
#define ADDRESSBOOK_INCLUDE_MESSAGE_PACKET_AND_UNPACKING_H_

#include "message.h"
#include <string>

class MessagePacket{
public:
  MessagePacket(const Message &m);
  std::string &get_packet(){ return m_packet_; }

private:
  std::string m_packet_;
};

class MessageUnpacking{
public:
  MessageUnpacking(const char *msg_buf);
  Message &get_message(){ return m_; }

private:
  std::string::iterator beg_2_end(std::string::iterator begin);
  Message m_;
};

#endif
