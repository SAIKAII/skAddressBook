#ifndef ADDRESSBOOK_INCLUDE_COMMUNICATIONSERVER_H_
#define ADDRESSBOOK_INCLUDE_COMMUNICATIONSERVER_H_

#include "client_server.h"
#include <unistd.h>

#define MAX_BUF 512

class CommunicationServer : public ClientServer{
public:
  CommunicationServer(int sockfd);
  void send_message();
  void recv_message();
  ~CommunicationServer(){}
};

#endif
