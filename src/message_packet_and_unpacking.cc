#include "../include/message_packet_and_unpacking.h"
#include "../util/base64_tool.h"
#include <algorithm>

const char *kName = "\\1";
const char *kIP = "\\2";
const char *kPort = "\\3";
const char *kMsg = "\\4";


MessagePacket::MessagePacket(const Message &m){
  std::string msg_encoded;
  base64_encode(m.get_msg(), &msg_encoded);
  m_packet_ += kName + m.get_name() + kIP + m.get_ip() + kPort + m.get_port()
                + kMsg + msg_encoded + "\n\n";
}

MessageUnpacking::MessageUnpacking(const char *msg_buf){
  char flag1, flag2;
  std::string msg(msg_buf);
  std::string::iterator msg_beg = msg.begin();
  std::string::iterator msg_end = msg_beg;
  do{
    flag1 = *msg_beg++;
    flag2 = *msg_beg++;
    if('\\' == flag1){
      msg_end = beg_2_end(msg_beg);
      if('1' == flag2){
        // ...log字段name开始拷贝
        std::string name(msg_beg, msg_end);
        m_.set_name(name);
        // ...log字段name拷贝完成
      }else if('2' == flag2){
        // ...log字段IP开始拷贝
        std::string ip(msg_beg, msg_end);
        m_.set_ip(ip);
        // ...log字段IP拷贝完成
      }else if('3' == flag2){
        // ...log字段Port开始拷贝
        std::string port(msg_beg, msg_end);
        m_.set_port(port);
        // ...log字段Port拷贝完成
      }else if('4' == flag2){
        // ...log字段msg开始拷贝
        std::string msg(msg_beg, msg_end);
        std::string out;
        base64_decode(msg, &out);
        m_.set_msg(out);
        // ...log字段msg拷贝完成
      }else{
        // ...log发现非法字段
        exit(1); // 后面可以考虑用异常处理，现在就这样处理
      }
      msg_beg = msg_end;
    }
  }while((flag1 != '\n' && flag2 != '\n') && msg_beg != msg.end());
}

std::string::iterator MessageUnpacking::beg_2_end(std::string::iterator begin){
  while('\\' != *begin && '\n' != *begin) ++begin;
  return begin;
}
