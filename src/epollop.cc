#include "../include/epollop.h"
#include "../include/communicationclient.h"
#include "../include/communicationserver.h"
#include <functional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <strings.h>

EpollOP::EpollOP(){
  listenfd_ = -1;
  epollfd_ = epoll_create(10);  // 这里的数值在Linux 2.6.8之后已经无意义的，但是必须是大于0
  if(-1 == epollfd_){
    // ...log创建失败
    exit(1);
  }
  thr_ = std::thread(std::bind(&EpollOP::monitor, this));
}

void EpollOP::monitor(){
  epoll_event events[MAX_EVENTS];
  int nfds, conn_sock, n;
  while(true){
    nfds = epoll_wait(epollfd_, events, MAX_EVENTS, -1);
    if(-1 == nfds){
      // ...log epoll_wait出错了
      exit(1);
    }

    for(n = 0; n < nfds; ++n){
      if(events[n].data.fd == listenfd_)
        create_connect();
      else{
        do_use_fd(&events[n]);
      }
    }
  }
}

void EpollOP::set_listenfd(int listenfd){
  listenfd_ = listenfd;
  epoll_event ev;
  ev.data.fd = listenfd_;
  ev.events = EPOLLIN | EPOLLET;  // 这里真的要ET模式吗？会不会出问题？
  if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_ADD, listenfd_, &ev)){
    // ...log通信配置出错，程序无法正常运行
    exit(1);
  }
}

void EpollOP::del_listenfd(){
  epoll_event ev;
  if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_DEL, listenfd_, &ev)){
    // ...log退出通讯删除监听套接字失败
    exit(1);
  }
  listenfd_ = -1;
}

void EpollOP::create_connect(){
  sockaddr_in addr;
  socklen_t addrlen;
  int conn_sock = accept(listenfd_, (sockaddr*)&addr, &addrlen);
  if(-1 == conn_sock){
    // ...log监听套接字三次握手失败
    return;
  }
  int flags = fcntl(conn_sock, F_GETFL, 0);
  // ...log设置套接字非阻塞
  fcntl(conn_sock, F_SETFL, flags | O_NONBLOCK);
  add_event(conn_sock, new CommunicationServer(conn_sock), ACCEPT);
}

void EpollOP::add_event(const int sockfd, ClientServer *cs, const int flag){
  // ...log添加事件到内核事件表
  epoll_event ev;
  if(ACCEPT == flag || SEND == flag){
    ev.events = EPOLLIN | EPOLLET;
  }else if(CONNECT == flag){
    ev.events = EPOLLIN | EPOLLOUT;
  }
  ev.data.fd = sockfd;
  if(ACCEPT == flag || CONNECT == flag){
    if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_ADD, sockfd, &ev)){
      // ...log添加事件到内核事件表失败
      // 这里就不多做处理的，没加入就算了，等带计时器删掉相关套接字及资源
      return;
    }
  }else{
    if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_MOD, sockfd, &ev)){
      // ...log添加事件到内核事件表失败
      // 这里就不多做处理的，没加入就算了，等带计时器删掉相关套接字及资源
      return;
    }
  }
  // ...log添加事件到内核事件表成功
  cs_map_.insert(std::make_pair(sockfd, cs));
}

void EpollOP::del_event(const int sockfd){
  // ...log删除内核事件表中某个事件
  epoll_event ev;
  bzero((void*)&ev, sizeof(epoll_event));
  if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_DEL, sockfd, &ev)){
    // ...log在内核事件表中删除操作失败
    return;
  }
  cs_map_.erase(cs_map_.find(sockfd));
  // ...log在内核事件表中删除操作成功
}

void EpollOP::do_use_fd(epoll_event *ev){
  if((ev->events & EPOLLOUT) && (ev->events & EPOLLIN)){
    // ...log非阻塞connect失败了，无法与彼端三次握手
    del_event(ev->data.fd);
  }else if(ev->events & EPOLLOUT){
    // 暂时来说，会符合该条件的，只有：connect成功了
    ClientServer *cs_ptr = (cs_map_.find(ev->data.fd))->second;
    cs_ptr->send_message();
  }else if(ev->events & EPOLLIN){
    std::unordered_map<int, ClientServer*>::iterator it = cs_map_.find(ev->data.fd);
    ClientServer *cs = it->second;
    cs->recv_message();
  }
}

EpollOP::~EpollOP(){
  close(epollfd_);
}
