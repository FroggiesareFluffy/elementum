#include "aqua/connection.h"
#include <string>
#include <iostream>

int main()
{
  aqua::Connection c;
  c.Connect("127.0.0.1", 9000);
  std::string s;
  while (s != "quit"){
    std::getline(std::cin, s);
    c.Send(s);
  }
  c.Disconnect();
  return 0;
}
