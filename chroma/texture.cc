#include "chroma/texture.h"
#include <GL/glew.h>

namespace chroma {

Texture::Texture() {
  glGenTextures(1, &_texture_);
}

Texture::~Texture() {
  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &_texture_);
}
  
void Texture::Bind(int location) {
  switch (location) {
  case 2: glActiveTexture(GL_TEXTURE2); break;
  case 1: glActiveTexture(GL_TEXTURE1); break;
  case 0: glActiveTexture(GL_TEXTURE0); break;
  }
  glBindTexture(GL_TEXTURE_2D, _texture_);
}

void Texture::Fill(TextureData* data) {
  glBindTexture(GL_TEXTURE_2D, _texture_);

  // Load Texture
  glTexImage2D(GL_TEXTURE_2D, 0, data->InternalFormat(),
	       data->Width(), data->Height(), 0,
	       data->Format(), GL_UNSIGNED_BYTE, data->Data());

  // Generate MipMap
  glGenerateMipmap(GL_TEXTURE_2D);

  // Set it to display nearest pixel while interpolating
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // Set it to clamp to edge
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
  
}  // namespace chroma
