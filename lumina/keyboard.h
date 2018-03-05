#ifndef LUMINA_KEYBOARD
#define LUMINA_KEYBOARD

#include <functional>
#include <string>

namespace lumina {

class Keyboard {
 public:
  Keyboard(const std::string& name = "default");
  ~Keyboard();
  void KeyDown(char c);
  void KeyUp(char c);
  void SetKeyDownAction(const std::function<void(char)>& function);
  void SetKeyUpAction(const std::function<void(char)>& function);
 private:
  std::function<void(char)> _keydown_;
  std::function<void(char)> _keyup_;
  std::string _name_;
};

}  // namespace lumina

#endif
