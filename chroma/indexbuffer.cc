#include "chroma/indexbuffer.h"
#include <GL/glew.h>
#include "chroma/chroma.h"
#include <iostream>

namespace chroma {

void IndexBuffer::Fill(std::vector<int>* data) {
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->size() * sizeof(int),
	       data->data(), GL_STATIC_DRAW);
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not fill index buffer\n";
  }
}

IndexBuffer::IndexBuffer() {
  chroma::Chroma::Get();
  glGenBuffers(1, &_buffer_);
    if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not create index buffer\n";
  }
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &_buffer_);
}
  
void IndexBuffer::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_);
}

void IndexBuffer::UnBind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

  
}  // namespace chroma
