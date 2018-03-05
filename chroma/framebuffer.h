#ifndef CHROMA_FRAME_BUFFER
#define CHROMA_FRAME_BUFFER

#include <GL/glew.h>

namespace chroma {

class FrameBuffer {
 public:
  FrameBuffer();
  ~FrameBuffer();
  void BindDraw();
  void BindRead();
  void Bind();
  void UnBind();
 private:
  GLuint _fbo_;
};
  
}  // namespace chroma

#endif
