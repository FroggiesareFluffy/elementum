#ifndef CHROMA_PROGRAM
#define CHROMA_PROGRAM

#include <GL/glew.h>
#include <memory>
#include "chroma/shader.h"

namespace chroma {

class Program {
 public:
  Program();
  ~Program();
  bool Link(const std::shared_ptr<Shader>& vertex_shader,
	    const std::shared_ptr<Shader>& fragment_shader);
  void Start();
  void Stop();
 private:
  GLuint _program_;
  std::shared_ptr<Shader> _vertex_shader_;
  std::shared_ptr<Shader> _fragment_shader_;

  friend class Uniform;
};
  
}  // namespace chroma

#endif
