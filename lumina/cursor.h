#ifndef LUMINA_CURSOR
#define LUMINA_CURSOR

#include <functional>
#include <string>

namespace lumina {

class Cursor {
 public:
  Cursor(const std::string& name = "default");
  ~Cursor();
  void LeftClick();
  void RightClick();
  void MiddleClick();
  void Move(int x, int y);
  void SetLeftClickAction(const std::function<void(void)>& function);
  void SetRightClickAction(const std::function<void(void)>& function);
  void SetMiddleClickAction(const std::function<void(void)>& function);
  void SetMoveAction(const std::function<void(int, int)>& function);
 private:
  std::function<void(void)> _leftclick_;
  std::function<void(void)> _rightclick_;
  std::function<void(void)> _middleclick_;
  std::function<void(int x, int y)> _move_;
  std::string _name_;
};
  
};  // namespace lumina

#endif
