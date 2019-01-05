#include "../include/event_timer.h"
#include "../include/epollop.h"
#include <chrono>
#include <ctime>
#include <functional> // std::bind()

EventTimer::EventTimer(){
  thr_ = std::thread(std::bind(&EventTimer::event_wait, this)); // 这里这样绑定成员函数和对象指定才能创建成功
}

void EventTimer::event_wait(){
  while(true){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    if(manager_list_.empty())
      continue;
    ObjectManager *obj_ptr = nullptr;
    while(!manager_list_.empty()){
      // 这里应该来个锁
      obj_ptr = manager_list_.front();
      CommunicationClient *comm_ptr = obj_ptr->comm_ptr_;
      if(obj_ptr->del_){
        manager_list_.pop_front();
        delete obj_ptr;
        continue;
      }else if(std::difftime(std::time(nullptr), comm_ptr->get_time()) < 2.0){
        break;
      }
      manager_list_.pop_front();
      // 这里解锁
      // 超过时间还没有指定事件发生，所以要删除了
      EpollOP *epoll_op = EpollOP::get_instance();
      epoll_op->del_event(comm_ptr->get_sockfd());
      del(comm_ptr->get_sockfd());
      delete obj_ptr;
    }
  }
}

void EventTimer::add(CommunicationClient *event){
  ObjectManager *ptr = new ObjectManager(event);
  manager_list_.push_back(ptr);
  manager_map_.insert(std::make_pair(event->get_sockfd(), ptr));
}

void EventTimer::del(const int sockfd){
  std::map<int, ObjectManager*>::iterator it = manager_map_.find(sockfd);
  delete it->second->comm_ptr_;
  it->second->del_ = true;
  manager_map_.erase(it);
}
