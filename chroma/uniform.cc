#include "chroma/uniform.h"
#include <GL/glew.h>
#include <string>
#include <vector>
#include "shadow/matrix.h"
#include "shadow/vector.h"

namespace chroma {

Uniform::Uniform(const std::string& name,
		 const Program& shader) {
  _uniform_ = glGetUniformLocation(shader._program_, name.c_str());
}
  
void Uniform::Set(float value) {
  glUniform1f(_uniform_, value);
}

void Uniform::Set(const shadow::Matrix& matrix) {
  glUniformMatrix4fv(_uniform_, 1, GL_FALSE, matrix.m);
}
  
void Uniform::Set(const shadow::Vector& vector) {
  glUniform4fv(_uniform_, 1, &vector.x);
}

void Uniform::Set(const std::vector<float>& values, int size) {
  switch (size) {
  case 4:
    glUniform4fv(_uniform_, values.size(), values.data()); break;
  case 3:
    glUniform3fv(_uniform_, values.size(), values.data()); break;
  case 2:
    glUniform2fv(_uniform_, values.size(), values.data()); break;
  default:
    glUniform1fv(_uniform_, values.size(), values.data()); break;
  }
}

}  // namespace chroma
