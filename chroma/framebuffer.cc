#include "chroma/framebuffer.h"
#include <GL/glew.h>

namespace chroma {

FrameBuffer::FrameBuffer() {
  glGenFramebuffers(1, &_fbo_);
}

FrameBuffer::~FrameBuffer() {
  glDeleteFramebuffers(1, &_fbo_);
}

void FrameBuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, _fbo_);
}

void FrameBuffer::BindDraw() {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo_);
}

void FrameBuffer::BindRead() {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo_);
}

void FrameBuffer::UnBind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
  
}  // namespace chroma
