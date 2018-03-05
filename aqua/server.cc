#include "aqua/server.h"
#include "aqua/connection.h"
#include <iostream>
#include <cstring>
#include <string>
#include "thirdparty/udt4/src/udt.h"
#include <arpa/inet.h>
#include <thread>

namespace aqua {

Server::Server() {
  _socket_ = 0;
  _online_ = false;
}

Server::~Server() {
  if (_socket_) Shutdown();
}

bool Server::Bind(int port) {
  _socket_ = UDT::socket(AF_INET, SOCK_STREAM, 0);
  
  _address_.sin_family = AF_INET;
  _address_.sin_port = htons(port);
  _address_.sin_addr.s_addr = INADDR_ANY;
  memset(&(_address_.sin_zero), '\0', 8);
  
  if (UDT::ERROR == UDT::bind(_socket_, (sockaddr*) &_address_,
			      sizeof(_address_))) {
    std::cout << "bind: " << UDT::getlasterror().getErrorMessage();
    return _online_ = false;
  }
  return _online_ = true;
}

void Server::Listen() {
  //std::cout << "Listening\n";
  UDT::listen(_socket_, 3); // Three in queue at a time
  auto start_connections = [this](){
    while (_socket_) {
      Connection* c = new Connection();
      c->Connect(_socket_);
      auto handle_connection = [c](){
	std::string s;
	while (c->Connected()) {
	  c->Receive(&s);
	  std::cout << s << std::endl;
	}
	delete c;
      };
      std::thread handle(handle_connection);
      handle.detach();
    }
  };
  std::thread start(start_connections);
  start.detach();
  //start_connections();
}

void Server::Shutdown() {
  UDT::close(_socket_);
  _socket_ = 0;
  _online_ = false;
}

}  // namespace aqua
