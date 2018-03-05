#include "prisma/model.h"
#include <fstream>
#include <iostream>

namespace prisma {

void Material::Serialize(std::ostream& os) const override {
  os << ambient.r << " " << ambient.g << " "
     << ambient.b << " " << ambient.a << " "
     << diffuse.r << " " << diffuse.g << " "
     << diffuse.b << " " << diffuse.a << " "
     << specular.r << " " << specular.g << " "
     << specular.b << " " << specular.a << " ";
}
  
void Material::Unserialize(std::istream& is) override {
  is >> ambient.r >> ambient.g >> ambient.b >> ambient.a
     >> diffuse.r >> diffuse.g >> diffuse.b >> diffuse.a
     >> specular.r >> specular.g >> specular.b >> specular.a;
}
  
void Transform::Serialize(std::ostream& os) const override {
  os << position.x << " " << position.y << " " << position.z << " "
     << rotation.x << " " << rotation.y << " " << rotation.z << " "
     << scale.x << " " << scale.y << " " << scale.z << " ";
}
  
void Transform::Unserialize(std::istream& is) override {
  is >> position.x >> position.y >> position.z
     >> rotation.x >> rotation.y >> rotation.z
     >> scale.x >> scale.y >> scale.z;
}

void Animation::Serialize(std::ostream& os) const override {
  os << transforms;
}
  
void Animation::Unserialize(std::istream& is) override {
  is >> transforms;
}

  
void Component::Serialize(std::ostream& os) {
  os << vertex_positions
     << vertex_colors
     << texture_coordinates
     << indices
     << animations
     << material;
}

void Component::Unserialize(std::istream& is) {
  is >> vertex_positions
     >> vertex_colors
     >> texture_coordinates
     >> indices
     >> animations
     >> material;
}
  
Model::Model() {
}
  
Model::Model(const std::string& filename) {
  std::ifstream fin;
  fin.open(filename.c_str());
  if (fin.fail()) {
    std::cout << "Couldn't save file " << filename << std::endl;
    return;
  }
  Unserialize(fin);
  fin.close();
}

void Model::Serialize(std::ostream& os) const override {
  os << components;
  os << materials;
}

void Model::Unserialize(std::istream& is) override {
  is >> components;
  is >> materials;
}

void Model::Save(const std::string& filename) {
  std::ofstream fout;
  fout.open(filename.c_str());
  if (fout.fail()) {
    std::cout << "Couldn't save file " << filename << std::endl;
    return;
  }
  Serialize(fout);
  fout.close();
}
  
}  // namespace prisma
