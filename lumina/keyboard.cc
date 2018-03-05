#include "lumina/keyboard.h"
#include "lumina/lumina.h"

namespace lumina {

Keyboard::Keyboard(const std::string& name) {
  _name_ = name;
  Lumina::Get().keyboards[_name_] = this;
}

Keyboard::~Keyboard() {
  Lumina::Get().keyboards.erase(_name_);
}

void Keyboard::KeyDown(char c){
  if (_keydown_) _keydown_(c);
}
  
void Keyboard::KeyUp(char c){
  if (_keyup_) _keyup_(c);
}
  
void Keyboard::
SetKeyDownAction(const std::function<void(char)>& function){
  _keydown_ = function;
}
  
void Keyboard::
SetKeyUpAction(const std::function<void(char)>& function){
  _keyup_ = function;
}

}
