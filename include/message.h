#ifndef ADDRESSBOOK_INCLUDE_MESSAGE_H_
#define ADDRESSBOOK_INCLUDE_MESSAGE_H_

#include <string>

const char *kName = "\\1";
const char *kIP = "\\2";
const char *kPort = "\\3";
const char *kMsg = "\\4";

class Message{
public:
  Message() = default;
  Message(const std::string &name, const std::string &ip, const std::string &port, const std::string &msg)
    : name_(name), ip_(ip), port_(port), msg_(msg){};
  std::string get_name() const { return name_; }
  std::string get_ip() const { return ip_; }
  std::string get_msg() const { return msg_; }
  std::string get_port() const { return port_; }
  void set_name(const std::string &name){ name_ = name; }
  void set_ip(const std::string &ip){ ip_ = ip; }
  void set_port(const std::string &port){ port_ = port; }
  void set_msg(const std::string &msg){ msg_ = msg; }

private:
  std::string name_, ip_, port_, msg_;
};

#endif
