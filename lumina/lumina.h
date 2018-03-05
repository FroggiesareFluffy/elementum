#ifndef LUMINA
#define LUMINA

#include <functional>
#include <map>
#include <memory>
#include "lumina/cursor.h"
#include "lumina/keyboard.h"
#include "lumina/window.h"

namespace lumina {

class Window;
  
/********************************************************
 * Singleton that makes sure Lumina (SDL2) is initialized
 * Lumina takes care of direct user I/O
 ********************************************************/
class Lumina {
 public:
  static Lumina& Get();
  Lumina(Lumina const&) = delete;
  void operator=(Lumina const&) = delete;
  void Update();
  void SetExitFunction(const std::function<void(void)>& function);
  ~Lumina();
  std::map<std::string, Window*> windows;
  std::map<std::string, Keyboard*> keyboards;
  std::map<std::string, Cursor*> cursors;
 private:
  Lumina();
  std::function<void(void)> _exitfunction_;
};

}

#endif
