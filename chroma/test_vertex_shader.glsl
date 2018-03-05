#version 400

layout(location = 0) in vec2 in_Position;
layout(location = 1) in vec3 in_Color;
layout(location = 2) in vec2 in_Texture;

out vec2 ex_Texture;
out vec3 ex_Color;

void main(void) {
  gl_Position = vec4(in_Position, 0.0f, 1.0f);
  ex_Color = in_Color;
  ex_Texture = in_Texture;
}
