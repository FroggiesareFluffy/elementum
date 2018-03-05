#ifndef CHROMA
#define CHROMA

#include <GL/glew.h>
#include "chroma/context.h"

namespace chroma {

/************************************************
 * Singleton that takes care of OpenGL state
 ************************************************/
class Chroma {
 public:
  static Chroma& Get();
  Chroma(Chroma const&) = delete;
  void operator=(Chroma const&) = delete;
  ~Chroma();
  bool CheckError(GLenum result);
  Context* active_context;
 private:
  Chroma();
};

}  // namespace chroma

#endif 
