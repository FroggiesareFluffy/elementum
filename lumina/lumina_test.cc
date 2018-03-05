#include <memory>
#include "lumina/lumina.h"
#include "lumina/window.h"
#include "lumina/cursor.h"

int main(int argc, char** argv)
{
  lumina::Window main_window("Main", 700, 500);
  bool quit = false;
  lumina::Cursor cursor("Cursor");
  cursor.SetRightClickAction([&](){
      quit = true;
  });
  while (!quit) { lumina::Lumina::Get().Update(); }
  return 0;
}
