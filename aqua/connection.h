#include <string>
#include "thirdparty/udt4/src/udt.h"
#include <arpa/inet.h>

#ifndef AQUA_CONNECTION
#define AQUA_CONNECTION

namespace aqua {

class Connection {
 public:
  Connection();
  ~Connection();
  bool Connected() { return _connected_; };
  bool Connect(UDTSOCKET server_socket);  // Server
  bool Connect(const std::string& ip, int port);  // Client
  bool Send(const std::string& message);
  bool Receive(std::string* message);
  void Disconnect();
 private:
  UDTSOCKET _socket_;
  sockaddr_in _address_;
  void SendSize(int size);
  void ReceiveSize(int* size);
  bool _connected_;
};

}  // namespace aqua

#endif
