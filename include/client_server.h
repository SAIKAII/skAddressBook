#ifndef ADDRESSBOOK_INCLUDE_CLIENT_SERVER_H_
#define ADDRESSBOOK_INCLUDE_CLIENT_SERVER_H_

#include <ctime>
#include <unistd.h>

class ClientServer{
public:
  virtual void send_message() = 0;
  virtual void recv_message() = 0;
  void set_sockfd(int sockfd){ sockfd_ = sockfd; }
  int get_sockfd(){ return sockfd_; }
  void set_time(){ start_time_ = std::time(nullptr); }
  std::time_t get_time(){ return start_time_; }
  virtual ~ClientServer(){ close(sockfd_); };

private:
  int sockfd_;
  std::time_t start_time_;
};

#endif
