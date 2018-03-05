#include "lumina/cursor.h"
#include "lumina/lumina.h"

namespace lumina {

Cursor::Cursor(const std::string& name) {
  _name_ = name;
  Lumina::Get().cursors[_name_] = this;
}

Cursor::~Cursor() {
  Lumina::Get().cursors.erase(_name_);
}
  
void Cursor::LeftClick(){
  if (_leftclick_) _leftclick_();
}
  
void Cursor::RightClick(){
  if (_rightclick_) _rightclick_();
}
  
void Cursor::MiddleClick(){
  if (_middleclick_) _middleclick_();
}
  
void Cursor::Move(int x, int y){
  if (_move_) _move_(x, y);
}
  
void Cursor::
SetLeftClickAction(const std::function<void(void)>& function){
  _leftclick_ = function;
}
  
void Cursor::
SetRightClickAction(const std::function<void(void)>& function){
  _rightclick_ = function;
}
  
void Cursor::
SetMiddleClickAction(const std::function<void(void)>& function){
  _middleclick_ = function;
}
  
void Cursor::
SetMoveAction(const std::function<void(int, int)>& function){
  _move_ = function;
}

}  // namespace lumina
