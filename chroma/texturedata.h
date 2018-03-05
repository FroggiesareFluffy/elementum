#ifndef CHROMA_TEXTURE_DATA
#define CHROMA_TEXTURE_DATA

#include <string>
#include <SDL2/SDL_image.h>

namespace chroma {

class TextureData {
 public:
  TextureData(const std::string& filename);
  ~TextureData();
  int Format();
  int Height();
  int Width();
  int InternalFormat();
  void* Data();
 private:
  SDL_Surface* _surface_;
  int _format_;
  int _internalformat_;
};
  
}  // namespace chroma

#endif
