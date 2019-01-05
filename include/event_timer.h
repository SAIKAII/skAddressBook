#ifndef ADDRESSBOOK_INCLUDE_EVENT_TIMER_H_
#define ADDRESSBOOK_INCLUDE_EVENT_TIMER_H_

#include "communicationclient.h"
#include <list>
#include <map>
#include <thread>

struct ObjectManager{
  bool del_;
  CommunicationClient *comm_ptr_;
  ObjectManager(CommunicationClient *ptr) : comm_ptr_(ptr){ del_ = false; }
};

class EventTimer{
public:
  static EventTimer *get_instance(){
    static EventTimer event_timer;
    return &event_timer;
  }
  void add(CommunicationClient *);
  void del(const int);
private:
  EventTimer();
  void event_wait();

  std::list<ObjectManager*> manager_list_;
  std::map<int, ObjectManager*> manager_map_;
  std::thread thr_;
};

#endif
