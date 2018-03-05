#include "chroma/vertexarray.h"
#include "chroma/chroma.h"
#include "chroma/vertexbuffer.h"
#include "chroma/indexbuffer.h"
#include <iostream>

namespace chroma {

VertexArray::VertexArray() {
  chroma::Chroma::Get();
  glGenVertexArrays(1, &_vao_);
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not Create Vertex Array\n";
  }
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &_vao_);
}

void VertexArray::Bind() {
  glBindVertexArray(_vao_);
}

void VertexArray::UnBind() {
  glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(int attribute_number, int unit_size,
				  const std::
				  shared_ptr<VertexBuffer>& buffer){
  // Hold reference to buffer so it doesn't get destroyed
  _vertices_.push_back(buffer);
  // Bind the buffer to save the state and keep it in the VAO
  buffer->Bind();
  // Assign the attribute data
  glVertexAttribPointer(attribute_number, unit_size,
			GL_FLOAT, GL_FALSE, unit_size * sizeof(float), 0);
  // Enable the attribute location
  glEnableVertexAttribArray(attribute_number);
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not Add Vertex Buffer\n";
  }
}
  
void VertexArray::SetIndexBuffer(const std::
				 shared_ptr<IndexBuffer>& buffer) {
  _indices_ = buffer;
  buffer->Bind();
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not Set Index Buffer\n";
  }
}
  
}  // namespace chroma
