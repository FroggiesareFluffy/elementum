#ifndef CHROMA_VERTEX_BUFFER
#define CHROMA_VERTEX_BUFFER

#include <GL/glew.h>
#include <vector>

namespace chroma {

class VertexBuffer {
 public:
  VertexBuffer();
  ~VertexBuffer();
  void Fill(std::vector<float>* data);
  void Bind();
  void UnBind();
 private:
  bool _bound_;
  GLuint _buffer_;
};
  
}  // namespace chroma

#endif
