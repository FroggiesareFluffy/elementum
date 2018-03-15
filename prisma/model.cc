#include "aqua/serializable.h"
#include "prisma/model.h"
#include <fstream>
#include <iostream>

namespace prisma {

void Material::Serialize(std::ostream& os) const override {
  os << ambient.r  << " " << ambient.g  << " "
     << ambient.b  << " " << ambient.a  << " "
     << diffuse.r  << " " << diffuse.g  << " "
     << diffuse.b  << " " << diffuse.a  << " "
     << specular.r << " " << specular.g << " "
     << specular.b << " " << specular.a << " ";

  os << ambient_texture  << " "
     << diffuse_texture  << " "
     << specular_texture << " "
     << normal_texture   << " ";

  os << vertex_shader << " "
     << fragment_shader;
}
  
void Material::Unserialize(std::istream& is) override {
  is >> ambient.r >> ambient.g >> ambient.b >> ambient.a
     >> diffuse.r >> diffuse.g >> diffuse.b >> diffuse.a
     >> specular.r >> specular.g >> specular.b >> specular.a;

  is >> ambient_texture >> diffuse_texture
     >> specular_texture >> normal_texture;

  is >> vertex_shader >> fragment_shader;
}
  
void Keyframe::Serialize(std::ostream& os) const override {
  os << bones;
}
  
void Keyframe::Unserialize(std::istream& is) override {
  is >> bones;
}

void Animation::Serialize(std::ostream& os) const override {
  os << transforms;
}
  
void Animation::Unserialize(std::istream& is) override {
  is >> transforms;
}

  
void Component::Serialize(std::ostream& os) {
  os << indices << " " << material;
}

void Component::Unserialize(std::istream& is) {
  is >> indices >> material;
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
  os << vertex_positions << " " << vertex_normals      << " "
     << vertex_colors    << " " << texture_coordinates << " "
     << vertex_bones     << " " << components          << " "
     << animations       << " " << materials;
}

void Model::Unserialize(std::istream& is) override {
  is >> vertex_positions >> vertex_normals
     >> vertex_colors    >> texture_coordinates
     >> vertex_bones     >> components
     >> animations       >> materials;
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
