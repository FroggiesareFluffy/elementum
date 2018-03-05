#include "chroma/vertexbuffer.h"
#include <GL/glew.h>
#include "chroma/chroma.h"
#include <iostream>

namespace chroma {

void VertexBuffer::Fill(std::vector<float>* data) {
  Bind();
  glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(float),
	       data->data(), GL_STATIC_DRAW);
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not fill Vertex Buffer\n";
  }
}

VertexBuffer::VertexBuffer() {
  chroma::Chroma::Get();
  glGenBuffers(1, &_buffer_);
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not create Vertex Buffer\n";
  }
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &_buffer_);
}
  
void VertexBuffer::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_);
}

void VertexBuffer::UnBind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

  
}  // namespace chroma
