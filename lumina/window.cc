#include "lumina/lumina.h"
#include "lumina/window.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <memory>

namespace lumina {

Window::Window(const std::string& title, int width, int height) {
  _title_ = title;
  Lumina::Get().windows[_title_] = this;
  _window_ = SDL_CreateWindow(_title_.c_str(),
			      SDL_WINDOWPOS_CENTERED,
			      SDL_WINDOWPOS_CENTERED,
			      width, height,
			      SDL_WINDOW_OPENGL |
			      SDL_WINDOW_SHOWN |
			      SDL_WINDOW_RESIZABLE);
  if (!_window_) throw "Error: Could not create window\n";
  _context_ = std::make_shared<chroma::Context>(_window_, width, height);
}

Window::~Window() {
  Lumina::Get().windows.erase(_title_);
  SDL_DestroyWindow(_window_);
}

std::shared_ptr<chroma::Context> Window::Context() {
  return _context_;
}

void Window::
SetResizeAction(const std::function<void(int, int)>& function) {
  _resize_ = function;
}

void Window::Render() {
  SDL_GL_SwapWindow(_window_);
}

unsigned int Window::Id() {
  return SDL_GetWindowID(_window_);
}
  
void Window::SetSize(int width, int height) {
  SDL_SetWindowSize(_window_, width, height);
  Resize(width, height);
}

void Window::Resize(int width, int height) {
  if (_resize_) _resize_(width, height);
}

void Window::GetSize(int* width, int* height) {
  SDL_GetWindowSize(_window_, width, height);
}
  
}
