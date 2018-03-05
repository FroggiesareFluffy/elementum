#ifndef CHROMA_INDEX_BUFFER
#define CHROMA_INDEX_BUFFER

#include <GL/glew.h>
#include <vector>

namespace chroma {

class IndexBuffer {
 public:
  IndexBuffer();
  ~IndexBuffer();
  void Fill(std::vector<int>* data);
  void Bind();
  void UnBind();
 private:
  GLuint _buffer_;
};
  
}  // namespace chroma

#endif
