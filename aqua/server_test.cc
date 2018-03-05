#include "aqua/server.h"
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
  aqua::Server s;
  s.Bind(9000);
  s.Listen();
  std::string input;
  while (input != "quit") {
    std::getline(std::cin, input);
  }
  s.Shutdown();
  return 0;
}
