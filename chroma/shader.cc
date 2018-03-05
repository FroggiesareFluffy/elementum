#include "chroma/shader.h"
#include "chroma/chroma.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace chroma {

GLuint Shader::ID() {
  return _shader_;
}

bool Shader::Compile(const std::string& filename) {
  std::ifstream fin;
  fin.open(filename.c_str());
  if (fin.fail()) {
    std::cout << "Error: Could not read shader program\n";
    return false;
  }
  std::string source;
  std::string line;
  while (getline(fin, line)) source += line + "\n";
  Compile(&source);
}
  
bool Shader::Compile(std::string* source) {
  // Add Source
  const GLchar* contents = source->c_str();
  glShaderSource(_shader_, 1, &contents, NULL);

  // Compile
  glCompileShader(_shader_);

  // Check Error
  GLint is_compiled = 0;
  glGetShaderiv(_shader_, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(_shader_, GL_INFO_LOG_LENGTH, &max_length);
    std::vector<GLchar> error_log(max_length);
    glGetShaderInfoLog(_shader_, max_length, &max_length, &error_log[0]);
    for (auto error : error_log) std::cout << error;
    std::cout << std::endl;
  }
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not compile shader\n";
    return false;
  }
  return true;
}
  
VertexShader::VertexShader() {
  chroma::Chroma::Get();
  _shader_ = glCreateShader(GL_VERTEX_SHADER);
}

VertexShader::~VertexShader() {
  glDeleteShader(_shader_);
}

FragmentShader::FragmentShader() {
  chroma::Chroma::Get();
  _shader_ = glCreateShader(GL_FRAGMENT_SHADER);
}

FragmentShader::~FragmentShader() {
  glDeleteShader(_shader_);
}

}  // namespace chroma
