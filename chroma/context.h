#ifndef CHROMA_CONTEXT
#define CHROMA_CONTEXT

#include <memory>
#include "SDL2/SDL.h"
#include "chroma/vertexarray.h"

namespace chroma {

class Context {
 public:
  Context(SDL_Window* window, int width, int height);
  ~Context();
  void Clear();
  void Clear(float r, float g, float b, float a);
  void SetMVP();
  void DrawTriangles(int num_triangles, long offset=0);
  void DrawLines(int num_lines, long offset=0);
  void SetSize(int width, int height);
 private:
  SDL_GLContext _context_;
  SDL_Window* _window_;
  void Enable();
  void MakeCurrent();
};
  
}  // namespace chroma

#endif
