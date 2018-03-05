#include "chroma/context.h"
#include "SDL2/SDL.h"
#include "chroma/chroma.h"

namespace chroma {

Context::Context(SDL_Window* window, int width, int height) {
  _window_ = window;
  _context_ = SDL_GL_CreateContext(_window_);
  if (!_context_) throw "Error: Could not create context\n";
  Enable();
  SDL_GL_SetSwapInterval(1);
  SetSize(width, height);
}

Context::~Context() {
}

void Context::SetSize(int width, int height) {
  MakeCurrent();
  glViewport(0, 0, width, height);
}

void Context::Enable() {
  SDL_GL_MakeCurrent(_window_, _context_);
  Chroma::Get().active_context = this;
}

void Context::Clear() {
  MakeCurrent();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Context::Clear(float r, float g, float b, float a) {
  MakeCurrent();
  glClearColor(r, g, b, a);
  Clear();
}

void Context::SetMVP() {
}

void Context::DrawTriangles(int num_triangles, long offset) {
  MakeCurrent();
  glDrawElements(GL_TRIANGLES, num_triangles * 3, GL_UNSIGNED_INT,
		 (GLvoid*)(offset * 4));
}

void Context::DrawLines(int num_lines, long offset) {
  MakeCurrent();
  glDrawElements(GL_LINES, num_lines * 2, GL_UNSIGNED_INT,
		 (GLvoid*)(offset * 4));
}

void Context::MakeCurrent() {
  if (Chroma::Get().active_context == this) return;
  Enable();
}
  
}  // namespace chroma
