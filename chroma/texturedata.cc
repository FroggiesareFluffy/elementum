#include "chroma/texturedata.h"
#include <iostream>
#include <GL/glew.h>

namespace chroma {

TextureData::TextureData(const std::string& filename) {
  _surface_ = IMG_Load(filename.c_str());

  if (!_surface_) {
    std::cout << "Failed to load " << filename << "\n";
    return;
  }

  std::string extension = filename.substr(filename.find_last_of(".") + 1);

  if (_surface_->format->BytesPerPixel == 4) {
    _format_ = (extension == "tga") ? GL_BGRA : GL_RGBA;
    _internalformat_ = GL_RGBA;
  } else {
    _format_ = (extension == "tga") ? GL_BGR : GL_RGB;
    _internalformat_ = GL_RGB;
  }
}

TextureData::~TextureData() {
  SDL_free(_surface_);
}

int TextureData::Format() {
  return _format_;
}

int TextureData::InternalFormat() {
  return _internalformat_;
}
  
int TextureData::Width() {
  return _surface_->w;
}

int TextureData::Height() {
  return _surface_->h;
}

void* TextureData::Data() {
  return _surface_->pixels;
}
  
}  // namespace chroma
