#ifndef PRISMA_MODEL
#define PRISMA_MODEL

#include "aqua/serializable.h"
#include "shadow/vector.h"
#include <vector>
#include <string>
#include <iostream>

namespace prisma {

// Pre-calculated Model Data to be read and optimized for rendering.
  
struct Material : public aqua::Serializable {

  shadow::Vector ambient_reflection;
  shadow::Vector diffuse_reflection;
  shadow::Vector specular_reflection;

  std::string ambient_texture;
  std::string diffuse_texture;
  std::string specular_texture;
  std::string normal_texture;

  std::string vertex_shader;
  std::string fragment_shader;

  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};

struct Keyframe : public aqua::Serializable {

  std::vector<shadow::Matrix> bones;

  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};
 
struct Animation : public aqua::Serializable {

  std::vector<Keyframe> keyframes;

  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};

struct Component : public aqua::Serializable {

  std::vector<int> indices;
  std::string material;

  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};
  
struct Model : public aqua::Serializable {

  Model();
  Model(const std::string& filename);

  std::string name;
  std::vector<float> vertex_positions;
  std::vector<float> vertex_normals;
  std::vector<float> vertex_colors;
  std::vector<float> texture_coordinates;
  std::vector<int> bones;
  std::vector<Component> components;
  std::map<std::string, Animation> animations;
  std::map<std::string, Material> materials;

  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
  void Save(const std::string& filename);
};
  
}  // namespace prisma

#endif
