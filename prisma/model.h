#ifndef PRISMA_MODEL
#define PRISMA_MODEL

#include "aqua/serializable.h"
#include "shadow/vector.h"
#include <vector>
#include <string>
#include <iostream>

namespace prisma {

struct Material : public aqua::Serializable {
  shadow::Vector ambient;
  shadow::Vector diffuse;
  shadow::Vector specular;
  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};
  
struct Transform : public aqua::Serializable {
  shadow::Vector position;
  shadow::Vector rotation;
  shadow::Vector scale;
  float duration;
  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};
  
struct Animation : public aqua::Serializable {
  std::vector<Transform> transforms;
  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};

struct Component : public aqua::Serializable {
  std::vector<float> vertex_positions;
  std::vector<float> vertex_colors;
  std::vector<float> texture_coordinates;
  std::vector<int> indices;
  std::map<std::string, Animation> animations;
  std::string material;
  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};
  
struct Model : public aqua::Serializable {
  Model();
  Model(const std::string& filename);
  std::vector<Component> components;
  std::map<std::string, Material> materials;
  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
  void Save(const std::string& filename);
};
  
}  // namespace prisma

#endif
