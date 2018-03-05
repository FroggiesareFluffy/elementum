#include "chroma/chroma.h"
#include "lumina/lumina.h"
#include <memory>
#include "chroma/vertexbuffer.h"
#include "chroma/indexbuffer.h"
#include "chroma/shader.h"
#include "chroma/program.h"
#include "chroma/vertexarray.h"
#include "chroma/context.h"
#include "lumina/window.h"
#include "lumina/cursor.h"
#include <iostream>
#include "chroma/texture.h"
#include "chroma/texturedata.h"

int main2(int argc, char** argv);

int main(int argc, char** argv) {
  try {
    main2(argc, argv);
  } catch (const char* e) {
    std::cout << e << std::endl;
    return 1;
  }
  return 0;
}

int main2(int argc, char** argv) {
  lumina::Window main_window("Main", 700, 500);
  lumina::Keyboard keyboard;
  bool quit = false;
  keyboard.SetKeyDownAction([&](char c){ quit = c == 'q'; });
  lumina::Lumina::Get().SetExitFunction([&](){ quit = true; });
  auto ctx = main_window.Context();
  main_window.SetResizeAction(
    [&](int width, int height){ ctx->SetSize(width, height); });

  auto positions = std::make_shared<chroma::VertexBuffer>();
  auto colors = std::make_shared<chroma::VertexBuffer>();
  auto texture_coordinates = std::make_shared<chroma::VertexBuffer>();
  auto indices = std::make_shared<chroma::IndexBuffer>();

  std::vector<float> position_data = { 0.f, .8f,
				       -.7f, -.8f,
				       .7f, -.8f };
  std::vector<float> color_data = { 1.f, 0.f, 0.f,
				    0.f, 1.f, 0.f,
				    0.f, 0.f, 1.f };
  std::vector<float> texture_coordinate_data = { 0.5f, .9f,
						 .15f, .1f,
						 .85f, .1f };
  std::vector<int> index_data = { 0, 1, 2 };

  positions->Fill(&position_data);
  colors->Fill(&color_data);
  texture_coordinates->Fill(&texture_coordinate_data);
  indices->Fill(&index_data);

  auto vertex_array = std::make_shared<chroma::VertexArray>();
  vertex_array->Bind();
  vertex_array->AddVertexBuffer(0, 2, positions);
  vertex_array->AddVertexBuffer(1, 3, colors);
  vertex_array->AddVertexBuffer(2, 2, texture_coordinates);
  vertex_array->SetIndexBuffer(indices);

  chroma::TextureData sc("textures/scales.jpg");
  chroma::Texture scales;
  scales.Fill(&sc);

  scales.Bind(0);
  
  auto vertex_shader = std::make_shared<chroma::VertexShader>();
  vertex_shader->Compile("test_vertex_shader.glsl");

  auto fragment_shader = std::make_shared<chroma::FragmentShader>();
  fragment_shader->Compile("test_fragment_shader.glsl");

  auto shader_program = std::make_shared<chroma::Program>();
  shader_program->Link(vertex_shader, fragment_shader);
  shader_program->Start();
  
  ctx->Clear(0.0f, 0.0f, 0.0f, 1.0f);
  
  while (!quit) {
    ctx->Clear();
    ctx->DrawTriangles(1);
    main_window.Render();
    lumina::Lumina::Get().Update();
  }
  return 0;
}
