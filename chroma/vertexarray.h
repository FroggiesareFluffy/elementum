#ifndef CHROMA_VERTEX_ARRAY
#define CHROMA_VERTEX_ARRAY

#include <GL/glew.h>
#include <vector>
#include <memory>
#include "chroma/vertexbuffer.h"
#include "chroma/indexbuffer.h"

namespace chroma {

class VertexArray {
 public:
  VertexArray();
  ~VertexArray();
  void Bind();
  void UnBind();
  void AddVertexBuffer(int attribute_number, int unit_size,
		       const std::shared_ptr<VertexBuffer>& buffer);
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);
 private:
  GLuint _vao_;
  std::vector<std::shared_ptr<VertexBuffer>> _vertices_;
  std::shared_ptr<IndexBuffer> _indices_;
};
  
}  // namespace chroma

#endif
