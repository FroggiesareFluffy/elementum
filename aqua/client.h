#include <string>
#include "thirdparty/udt4/src/udt.h"
#include <arpa/inet.h>

class Client {
public:
  Client(std::string ip, int port);
  bool Connect();
  void Disconnect();
  bool Send(std::string message);
private:
  UDTSOCKET _socket_;
  // Internet Address
  sockaddr_in _address_;
};
