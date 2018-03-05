#include "lumina/lumina.h"
#include "lumina/cursor.h"
#include "lumina/keyboard.h"
#include "lumina/window.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace lumina {

Lumina& Lumina::Get() {
  static Lumina instance;
  return instance;
}

Lumina::Lumina() {
  // Start up SDL2
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw "Error: Couldn't initialize Lumina";

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  _exitfunction_ = nullptr;
}

Lumina::~Lumina() {
  SDL_Quit();
}

void Lumina::SetExitFunction(const std::function<void(void)>& function) {
  _exitfunction_ = function;
}
  
void Lumina::Update() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      if (_exitfunction_) _exitfunction_();
      break;
    case SDL_WINDOWEVENT:
      switch (event.window.event) {
      case SDL_WINDOWEVENT_RESIZED:
	for (auto& window : windows) {
	  if (window.second->Id() == event.window.windowID)
	    window.second->Resize(event.window.data1,
				  event.window.data2);
	}
	break;
      default:
	break;
      }
      break;
    case SDL_MOUSEMOTION:
      int x, y;
      SDL_GetMouseState(&x, &y);
      for (auto& cursor : cursors) 
	cursor.second->Move(x, y);
      break;
    case SDL_KEYDOWN:
      for (auto& keyboard : keyboards) 
	keyboard.second->KeyDown(event.key.keysym.sym);
      break;
    case SDL_KEYUP:
      for (auto& keyboard : keyboards) 
	keyboard.second->KeyUp(event.key.keysym.sym);
      break;
    case SDL_MOUSEBUTTONDOWN:
      switch (event.button.button) {
      case SDL_BUTTON_LEFT:
	for (auto& cursor : cursors) 
	  cursor.second->LeftClick();
	break;
      case SDL_BUTTON_MIDDLE:
	for (auto& cursor : cursors) 
	  cursor.second->MiddleClick();
	break;
      case SDL_BUTTON_RIGHT:
	for (auto& cursor : cursors) 
	  cursor.second->RightClick();
	break;
      }
      break;
    default:
      break;
    }
  }
}
  
}  // namespace lumina
