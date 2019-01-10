#include "../include/communication.h"
#include "../include/epollop.h"
#include "../include/global_config.h"
#include "../include/communicationclient.h"
#include "../include/communicationserver.h"
#include <string>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>

void Communication::init(){
  // ...log进入通讯状态
  OnlineDBOP *onlinedbop = OnlineDBOP::get_instance();
  std::cout << "请输入想使用的本机端口号：";
  std::string port_str;
  int port;
  std::cin >> port_str;
  port = std::stoi(port_str);
  onlinedbop->init(port);
  GlobalConfig *global_config = GlobalConfig::get_instance();
  sockaddr_in servaddr;
  listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
  if(-1 == listenfd_){
    // ...log失败，无法通讯
    exit(1);
  }
  int flags = fcntl(listenfd_, F_GETFL, 0);
  fcntl(listenfd_, F_SETFL, flags | O_NONBLOCK);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  servaddr.sin_addr.s_addr = inet_addr(global_config->get_ip().c_str());
  if(-1 == bind(listenfd_, (sockaddr*)&servaddr, sizeof(servaddr))){
    // ...log绑定失败，无法通讯
    exit(1);
  }
  if(-1 == listen(listenfd_, 10)){
    // ...log监听套接字失败，无法通讯
    exit(1);
  }
  EpollOP *epoll_op = EpollOP::get_instance();
  epoll_op->set_listenfd(listenfd_);
}

void Communication::start(){
  OnlineDBOP *onlinedbop = OnlineDBOP::get_instance();
  int option;
  while(true){
    option = 0;
    print_all_onlines(onlinedbop);
    std::cout << "请输入想要联系的人：" << std::endl;
    std::cout << "1、信息发送给所有人" << std::endl;
    std::cout << "2、信息发送给指定的人" << std::endl;
    std::cout << "0、退出聊天" << std::endl;

    std::cin >> option;
    if(1 == option){
      comm_with_all();
    }else if(2 == option){
      comm_with_one();
    }else{
      break;
    }
  }
}

void Communication::print_all_onlines(OnlineDBOP *onlinedbop){
  std::string sql = "select id, name, ip, port "
                    "from online;";
  onlines_ = onlinedbop->query_onlines(sql);
  std::cout << std::setw(6) << "序号" << std::setw(12) << "姓名" << std::setw(19) << "IP地址"
  << std::setw(8) << "端口" << std::endl;
  // ...log开始打印所有“在线”人到屏幕
  int index = 0;
  for(auto online : *onlines_){
    std::cout << std::setw(4) << ++index;
    online.print_info();
  }
  // ...log所以“在线”人打印完毕
}

std::shared_ptr<MessagePacket> Communication::create_msg(){
  std::cout << "请输入想要发送的信息：";
  std::string msg;
  std::cin >> msg;
  GlobalConfig *global_config = GlobalConfig::get_instance();
  return std::shared_ptr<MessagePacket>(new MessagePacket(Message(global_config->get_name(),
                                        global_config->get_ip(), global_config->get_port(), msg)));
}

void Communication::comm_with_all(){
  while(true){
    std::cout << "是否确定要给以上所有人发送消息？(Y/n)：";
    std::string comfirm;
    std::cin >> comfirm;
    if(!comfirm.empty()){
      if(comfirm == "Y" || comfirm == "y"){
        // ...什么都不做
      }else{
        return;
      }
    }
    std::shared_ptr<MessagePacket> msg_ptr = create_msg();
    // ...log开始创建与每个人的网络套接字
    CommunicationClient *comm_client;
    for(auto online : *(onlines_)){
      comm_client = new CommunicationClient(online, msg_ptr);
    }
  }
}

void Communication::comm_with_one(){
  std::cout << "请输入想联系的人的序号：";
  int index;
  std::cin >> index;
  if(index <= 0 || index > onlines_->size()){
    // ...log输入错误的序号
    std::cout << "序号错误！" << std::endl;
    return;
  }

  Online online = (*onlines_)[index-1];
  ClientServer *comm_client;
  while(true){
    std::shared_ptr<MessagePacket> msg_ptr = create_msg();
    comm_client = new CommunicationClient(online, msg_ptr);
    std::cout << "是否要继续与该联系人通讯？(Y/n)：";
    std::string comfirm;
    std::cin >> comfirm;
    if(!comfirm.empty()){
      if(comfirm == "Y" || comfirm == "y"){
        // ...什么都不做
      }else{
        return;
      }
    }
  }
}

Communication::~Communication(){
  GlobalConfig *global_config = GlobalConfig::get_instance();
  std::string sql = "delete from online where ip = '"
                    + global_config->get_ip() + "' and port = '"
                    + global_config->get_port() + "';";
  OnlineDBOP *onlinedbop = OnlineDBOP::get_instance();
  onlinedbop->update_tbl_online(sql);
  EpollOP *epoll_op = EpollOP::get_instance();
  epoll_op->del_listenfd();
  close(listenfd_);
}
