#ifndef CHROMA_UNIFORM
#define CHROMA_UNIFORM

#include <GL/glew.h>
#include "chroma/program.h"
#include <string>
#include <vector>
#include "shadow/matrix.h"
#include "shadow/vector.h"

namespace chroma {

class Uniform {
 public:
  Uniform(const std::string& name,
	  const Program& shader);
  void Set(float value);
  void Set(const shadow::Matrix& matrix);
  void Set(const shadow::Vector& vector);
  void Set(const std::vector<float>& values, int size=1);
 private:
  GLuint _uniform_;
};

}  // namespace chroma

#endif
