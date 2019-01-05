#include "../include/communicationclient.h"
#include "../include/epollop.h"
#include "../include/event_timer.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string>

CommunicationClient::CommunicationClient(const Online &online, std::shared_ptr<MessagePacket> &msg_ptr){
  msg_ptr_ = msg_ptr;
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
  int flags = fcntl(sockfd_, F_GETFL, 0);
  // ...log设置套接字非阻塞
  fcntl(sockfd_, F_SETFL, flags | O_NONBLOCK);

  sockaddr_in addr;
  bzero((void*)&addr, sizeof(sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(std::stoi(online.get_port()));
  addr.sin_addr.s_addr = inet_addr(online.get_ip().c_str());
  // ...log将套接字加入epoll监控
  EpollOP *epoll_op = EpollOP::get_instance();
  epoll_op->add_connect(sockfd_);
  // ...log开始创建连接
  connect(sockfd_, (sockaddr*)&addr, sizeof(sockaddr_in));
}

void CommunicationClient::send_message(){
  // ...log开始发送信息。首先是进行监控。
  EpollOP *epoll_op = EpollOP::get_instance();
  epoll_op->add_send(sockfd_);
  EventTimer *event_timer = EventTimer::get_instance();
  event_timer->add(this);

  std::string &msg = msg_ptr_->get_packet();
  send(sockfd_, msg.c_str(), msg.length(), 0);
}

void CommunicationClient::recv_message(){
  // ...log接受到彼端的回复，从计时器中删除该套接字
  EventTimer *event_timer = EventTimer::get_instance();
  event_timer->del(sockfd_);
}
