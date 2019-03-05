#ifndef ADDRESSBOOK_INCLUDE_GLOBAL_CONFIG_H_
#define ADDRESSBOOK_INCLUDE_GLOBAL_CONFIG_H_

#include <string>

class GlobalConfig{
public:
  static GlobalConfig *get_instance(){
    static GlobalConfig global_config;
    return &global_config;
  }
  std::string get_name(){ return name_; }
  std::string get_ip(){ return ip_; }
  std::string get_port(){ return port_; }
  void set_port(const std::string &port){ port_ = port; }
  void set_ip(const std::string &ip){ ip_ = ip; }
  void set_name(const std::string &ip);

private:
  // GlobalConfig();
  std::string name_, ip_, port_;
};

#endif
