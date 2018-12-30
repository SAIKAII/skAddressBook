#include "../include/contact.h"
#include <iostream>
#include <iomanip>

inline int Contact::get_id() const{
  return id_;
}

inline std::string Contact::get_name() const{
  return name_;
}

inline std::string Contact::get_sex() const{
  return sex_;
}

inline std::string Contact::get_address() const{
  return address_;
}

inline std::string Contact::get_ip() const{
  return ip_;
}

inline void Contact::print_info() const{
  std::cout << std::ios::left << std::setw(10) << name_ << std::setw(4) << sex_
  << std::setw(20) << address_ << std::setw(17) << ip_ << std::endl;
}
