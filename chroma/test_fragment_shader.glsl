#version 400

in vec2 ex_Texture;
in vec3 ex_Color;
out vec4 out_Color;

uniform sampler2D sampler;

void main(void) {
  vec4 tex = texture(sampler, ex_Texture);
  vec4 color = vec4(ex_Color, 1.0f);
  out_Color = (color * .3) + (tex * .5);
}
