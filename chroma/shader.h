#ifndef CHROMA_SHADER
#define CHROMA_SHADER

#include <GL/glew.h>
#include <string>

namespace chroma {

class Shader {
 public:
  bool Compile(const std::string& filename);
  bool Compile(std::string* source);
  GLuint ID();
 protected:
  GLuint _shader_;
};

class VertexShader : public Shader {
 public:
  VertexShader();
  ~VertexShader();
};

class FragmentShader : public Shader {
 public:
  FragmentShader();
  ~FragmentShader();
};
  
}  // namespace chroma

#endif
