#include "../include/contact.h"
#include <iostream>
#include <iomanip>

int Contact::get_id() const{
  return id_;
}

std::string Contact::get_name() const{
  return name_;
}

std::string Contact::get_sex() const{
  return sex_;
}

std::string Contact::get_address() const{
  return address_;
}

std::string Contact::get_ip() const{
  return ip_;
}

void Contact::print_info() const{
  std::cout.flags(std::ios::left);
  std::cout << std::setw(10) << name_ << std::setw(10) << sex_
  << std::setw(20) << address_ << std::setw(17) << ip_ << std::endl;
}
