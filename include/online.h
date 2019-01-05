#ifndef ADDRESSBOOK_INCLUDE_ONLINE_H_
#define ADDRESSBOOK_INCLUDE_ONLINE_H_

#include <string>
#include <iostream>
#include <iomanip>

class Online{
public:
  Online(std::string name, std::string ip, std::string port)
    : name_(name), ip_(ip), port_(port){}
  Online(int id, std::string name, std::string ip, std::string port)
    : id_(id), name_(name), ip_(ip), port_(port){}
  const std::string get_name() const { return name_; }
  const std::string get_ip() const { return ip_; }
  const std::string get_port() const { return port_; }
  void print_info() const {
    std::cout.flags(std::ios::left);
    std::cout << std::setw(10) << name_ << std::setw(17) << ip_
    << std::setw(6) << port_ << std::endl;
  }

private:
  int id_;
  std::string name_, ip_, port_;
};

#endif
