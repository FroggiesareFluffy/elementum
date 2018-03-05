#include "chroma/program.h"
#include <GL/glew.h>
#include <memory>
#include <iostream>
#include <vector>

namespace chroma {
  
Program::Program() {
  _program_ = glCreateProgram();
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not create shader program\n";
  }
}

Program::~Program() {
  if (_vertex_shader_) glDetachShader(_program_, _vertex_shader_->ID());
  if (_fragment_shader_)
    glDetachShader(_program_, _fragment_shader_->ID());
  glDeleteProgram(_program_);
}

bool Program::Link(const std::shared_ptr<Shader>& vertex_shader,
		   const std::shared_ptr<Shader>& fragment_shader) {
  _vertex_shader_ = vertex_shader;
  _fragment_shader_ = fragment_shader;
  glAttachShader(_program_, vertex_shader->ID());
  glAttachShader(_program_, fragment_shader->ID());
  glLinkProgram(_program_);
  GLint is_linked = 0;
  glGetProgramiv(_program_, GL_LINK_STATUS, &is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glGetProgramiv(_program_, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glGetProgramInfoLog(_program_, max_length, &max_length, &info_log[0]);
    for (auto error : info_log) std::cout << error;
    std::cout << std::endl;
  }
  if (GL_NO_ERROR != glGetError()) {
    std::cout << "Error: Could not link shader program\n";
    return false;
  }
  return true;
}

void Program::Start() {
  glUseProgram(_program_);
}

void Program::Stop() {
  glUseProgram(0);
}

}  // namespace chroma
