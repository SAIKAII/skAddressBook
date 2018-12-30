#ifndef ADDRESSBOOK_INCLUDE_CONTACT_H_
#define ADDRESSBOOK_INCLUDE_CONTACT_H_

#include <string>

class Contact{
public:
  Contact(std::string name, std::string sex, std::string address, std::string ip)
    : name_(name), sex_(sex), address_(address), ip_(ip){}
  Contact(int id, std::string name, std::string sex, std::string address, std::string ip)
    : id_(id), name_(name), sex_(sex), address_(address), ip_(ip){}
  int get_id() const;
  std::string get_name() const;
  std::string get_sex() const;
  std::string get_address() const;
  std::string get_ip() const;
  void print_info() const;

private:
  int id_;
  std::string name_, sex_, address_, ip_;
};

#endif
