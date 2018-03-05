#include "aqua/connection.h"
#include <string>
#include "thirdparty/udt4/src/udt.h"
#include <arpa/inet.h>

#ifndef AQUA_SERVER
#define AQUA_SERVER

namespace aqua {

class Server {
 public:
  Server();
  ~Server();
  bool Bind(int port);
  bool Online() { return _online_; };
  void Listen();
  void Shutdown();
 private:
  UDTSOCKET _socket_;
  // server address
  sockaddr_in _address_;
  bool _online_;
};

}  // namespace aqua

#endif
