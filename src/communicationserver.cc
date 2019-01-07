#include "../include/communicationserver.h"
#include "../include/message_packet_and_unpacking.h"
#include "../include/message.h"
#include "../include/event_timer.h"
#include "../include/epollop.h"
#include <iostream>
#include <sys/socket.h>

CommunicationServer::CommunicationServer(int sockfd){
  set_sockfd(sockfd);
  EventTimer *event_timer = EventTimer::get_instance();
  event_timer->add(this);
}

void CommunicationServer::send_message(){
  char reply[7] = "200 OK";
  int len = 7;
  send(get_sockfd(), reply, len, 0);
  EpollOP *epoll_op = EpollOP::get_instance();
  epoll_op->del_event(get_sockfd());
  EventTimer *event_timer = EventTimer::get_instance();
  event_timer->del(get_sockfd());
}

void CommunicationServer::recv_message(){
  char buf[MAX_BUF];
  int n = recv(get_sockfd(), buf, MAX_BUF, 0);
  MessageUnpacking mu(buf);
  Message m = mu.get_message();
  std::cout << "姓名：" << m.get_name() << "\tIP：" << m.get_ip() << "\tPort：" << m.get_port() << std::endl;
  std::cout << "消息：" << m.get_msg() << std::endl;
  send_message();
}
