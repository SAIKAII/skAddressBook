#ifndef ADDRESSBOOK_INCLUDE_EVENT_TIMER_H_
#define ADDRESSBOOK_INCLUDE_EVENT_TIMER_H_

#include "communicationclient.h"
#include "communicationserver.h"
#include <list>
#include <unordered_map>
#include <thread>

struct ObjectManager{
  bool del_;
  ClientServer *cs_ptr_;
  ObjectManager(ClientServer *ptr) : cs_ptr_(ptr){ del_ = false; }
};

class EventTimer{
public:
  static EventTimer *get_instance(){
    static EventTimer event_timer;
    return &event_timer;
  }
  void add(ClientServer *);
  void del(const int);
private:
  EventTimer();
  void event_wait();

  std::list<ObjectManager*> manager_list_;
  std::unordered_map<int, ObjectManager*> manager_map_;
  std::thread thr_;
};

#endif
