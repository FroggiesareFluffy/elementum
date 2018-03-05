#ifndef CHROMA_TEXTURE
#define CHROMA_TEXTURE

#include <GL/glew.h>
#include "chroma/texturedata.h"

namespace chroma {

class Texture {
 public:
  Texture();
  ~Texture();
  void Bind(int location);
  void Fill(TextureData* data);
 private:
  GLuint _texture_;
};
  
}  // namespace chroma

#endif
