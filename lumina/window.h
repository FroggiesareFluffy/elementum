#ifndef LUMINA_WINDOW
#define LUMINA_WINDOW

#include <SDL2/SDL.h>
#include <string>
#include "lumina/lumina.h"
#include <functional>
#include <memory>
#include "chroma/context.h"

namespace lumina {

class Window {
 public:
  Window(const std::string& title, int width, int height);
  ~Window();
  unsigned int Id();
  void SetSize(int width, int height);
  void GetSize(int* width, int* height);
  void SetResizeAction(const std::function<void(int, int)>& function);
  void Render();
  std::shared_ptr<chroma::Context> Context();
 private:
  SDL_Window* _window_;
  std::function<void(int, int)> _resize_;
  std::string _title_;
  std::shared_ptr<chroma::Context> _context_;
  void Resize(int x, int y);
  friend class Lumina;
};

}  // namespace lumina

#endif
