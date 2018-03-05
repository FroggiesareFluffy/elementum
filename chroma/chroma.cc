#include <GL/glew.h>
#include "chroma/chroma.h"
#include <iostream>

namespace chroma {

Chroma& Chroma::Get() {
  static Chroma instance;
  return instance;
}
  
Chroma::Chroma() {
  glewExperimental = GL_TRUE;

  // Initialize GLEW
  if (CheckError(glewInit()))
    throw "Error: Could not initialize Glew";

  // Print Version
  std::cout << "INFO: OpenGL Version: "
	    << glGetString(GL_VERSION) << std::endl;

  glGetError();

  // Set Clear Color
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Enable Depth Buffering
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Enable Backface Culling
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  // Blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Check for Errors
  if (CheckError(glGetError()))
    std::cout << "OpenGL may not be properly configured";

  active_context = nullptr;
}

Chroma::~Chroma() {
}

bool Chroma::CheckError(GLenum result) {
  if (GLEW_OK != result){
    std::cout << "Error: "
	      << glewGetErrorString(result);
    return true;
  }
  return false;
}
  
}  // namespace chroma
