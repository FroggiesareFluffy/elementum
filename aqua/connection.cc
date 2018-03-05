#include "aqua/server.h"
#include <iostream>
#include <cstring>
#include <string>
#include "thirdparty/udt4/src/udt.h"
#include <arpa/inet.h>

namespace aqua {

Connection::Connection() {
  _socket_ = 0;
}

Connection::~Connection() {
  if (_socket_) Disconnect();
}
  
bool Connection::Connect(UDTSOCKET server_socket) {
  //std::cout << "Connecting to Client\n";
  int namelen;

  if (UDT::ERROR ==
      (_socket_ = UDT::accept(server_socket, (sockaddr*)&_address_,
			      &namelen))){
    std::cout << "connect: " << UDT::getlasterror().getErrorMessage();
    return _connected_ = false;
  }

  std::cout << "new connection: " << inet_ntoa(_address_.sin_addr)
	    << ":" << ntohs(_address_.sin_port) << std::endl;
  return _connected_ = true;
}

bool Connection::Connect(const std::string& ip, int port) {
  //std::cout << "Connecting to server\n";
  // Create the socket
  _socket_ = UDT::socket(AF_INET, SOCK_STREAM, 0);
  // Symbolic constant always set
  _address_.sin_family = AF_INET;
  // Set the destination port
  _address_.sin_port = htons(port);
  // Set the connection ip address (string to binary)
  inet_pton(AF_INET, ip.c_str(), &_address_.sin_addr);
  memset(&(_address_.sin_zero), '\0', 8);
  
  if (UDT::ERROR ==
      UDT::connect(_socket_, (sockaddr*)&_address_,
		   sizeof(_address_))) {
    std::cout << "connect: " << UDT::getlasterror().getErrorMessage();
    return _connected_ = false;
  }
  //std::cout << "Connection Successful\n";
  return _connected_ = true;
}

bool Connection::Send(const std::string& message) {
  //std::cout << "Sending Message\n";
  int offset = 0;
  int bytes_sent;
  SendSize(message.size() + 1);
  while (offset < message.size()) {
    if (UDT::ERROR ==
	(bytes_sent = UDT::send(_socket_, message.c_str() + offset,
			(message.size() + 1) - offset, 0))) {
      std::cout << "send: " << UDT::getlasterror().getErrorMessage();
      Disconnect();
      return false;
    }
    offset += bytes_sent;
  }
  //std::cout << "Sent " << message << std::endl;
  return true;
}

bool Connection::Receive(std::string* message) {
  //std::cout << "Waiting For Message\n";
  int size;
  ReceiveSize(&size);
  // Get the rest of the message
  char data[size];
  int offset = 0;
  int bytes_read;
  while (offset < size) {
    //std::cout << "Offset: " << offset << std::endl;
    if (UDT::ERROR ==
	(bytes_read = UDT::recv(_socket_, data + offset,
				size - offset, 0))) {
      std::cout << "recv:" << UDT::getlasterror().getErrorMessage()
		<< std::endl;
      Disconnect();
      return false;
    }
    offset += bytes_read;
  }
  *message = data;
  //std::cout << "Received Message " << *message << std::endl;
  return true;
}

void Connection::SendSize(int size) {
  char num_bytes[4];
  num_bytes[0] = static_cast<char>(size >> 24);
  num_bytes[1] = static_cast<char>(size >> 16);
  num_bytes[2] = static_cast<char>(size >> 8);
  num_bytes[3] = static_cast<char>(size);
  UDT::send(_socket_, num_bytes, 4, 0);
  //std::cout << "Sent " << size << "Bytes\n";
}

void Connection::ReceiveSize(int* size) {
  char num_bytes[4];
  if (UDT::ERROR == UDT::recv(_socket_, num_bytes, 4, 0)) {
    std::cout << "recv:" << UDT::getlasterror().getErrorMessage()
	      << std::endl;
    Disconnect();
    *size = 0;
    return;
  }
  *size =
    static_cast<int>(num_bytes[0]) << 24 |
    static_cast<int>(num_bytes[1]) << 16 |
    static_cast<int>(num_bytes[2]) << 8  |
    static_cast<int>(num_bytes[3]);
  //std::cout << "Received " << *size << "Bytes\n";
}

void Connection::Disconnect() {
  //std::cout << "Disconnecting\n";
  //std::cout << "Socket: " << _socket_ << std::endl;;
  UDT::close(_socket_);
  _socket_ = 0;
  _connected_ = false;
  //std::cout << "Socket: " << _socket_ << std::endl;
}

}  // namespace aqua
