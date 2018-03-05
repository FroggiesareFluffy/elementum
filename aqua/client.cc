#include "aqua/client.h"
#include <iostream>
#include <string>
#include <cstring>
#include "thirdparty/udt4/src/udt.h"
#include <arpa/inet.h>

Client::Client(std::string ip, int port) {
  // Create the socket
  _socket_ = UDT::socket(AF_INET, SOCK_STREAM, 0);
  // Symbolic constant always set
  _address_.sin_family = AF_INET;
  // Set the destination port
  _address_.sin_port = htons(port);
  // Set the connection ip address (string to binary)
  inet_pton(AF_INET, ip.c_str(), &_address_.sin_addr);
  memset(&(_address_.sin_zero), '\0', 8);
}

bool Client::Connect() {
  if (UDT::ERROR ==
      UDT::connect(_socket_, (sockaddr*)&_address_, sizeof(_address_))) {
    std::cout << "connect: " << UDT::getlasterror().getErrorMessage();
    return false;
  }
  return true;
}

void Client::Disconnect() {
  UDT::close(_socket_);
}

bool Client::Send(std::string message) {
  if (UDT::ERROR ==
      UDT::send(_socket_, message.c_str(), message.size() + 1, 0)) {
    std::cout << "send: " << UDT::getlasterror().getErrorMessage();
    return false;
  }
  return true;
}
