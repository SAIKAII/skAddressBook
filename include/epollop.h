#ifndef ADDRESSBOOK_INCLUDE_EPOLLOP_H_
#define ADDRESSBOOK_INCLUDE_EPOLLOP_H_

#include "client_server.h"
#include <thread>
#include <sys/epoll.h>
#include <unistd.h>
#include <unordered_map>

#define MAX_EVENTS 20
#define ACCEPT 1
#define CONNECT 2
#define SEND 3

class EpollOP{
public:
  static EpollOP *get_instance(){
    static EpollOP epoll_op;
    return &epoll_op;
  }
  void set_listenfd(int listenfd);
  void add_event(const int sockfd, ClientServer *cs, const int flag);
  void del_event(const int sockfd);
  ~EpollOP();

private:
  EpollOP();
  void monitor();
  void create_connect();
  void do_use_fd(epoll_event *ev);

  std::thread thr_;
  int epollfd_;
  int listenfd_;
  std::unordered_map<int, ClientServer*> cs_map_;
};

#endif
