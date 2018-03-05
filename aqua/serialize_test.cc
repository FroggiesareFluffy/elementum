#include "aqua/serializable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct Accident : public aqua::Serializable {

  void Serialize(std::ostream& out) const override {
    out << year << " " << owner << " " << loss_of_value;
  }
  void Unserialize(std::istream& in) {
    in >> year >> owner >> loss_of_value;
  }

  int year;
  std::string owner;
  float loss_of_value;

};

struct Car : public aqua::Serializable {

  void Serialize(std::ostream& out) const override {
    out << color << " " << year << " " << mileage << " ";
    out << most_recent_accident;
    out << owners;
    out << features;
  }
  void Unserialize(std::istream& in) override {
    in >> color >> year >> mileage;
    in >> most_recent_accident;
    in >> owners;
    in >> features;
  }

  std::string color;
  int year;
  float mileage;
  Accident most_recent_accident;
  std::vector<std::string> owners;
  std::map<std::string, int> features;
};

int main(int argc, char** argv) {
  Car my_car;
  my_car.color = "blue";
  my_car.mileage = 123456;
  my_car.owners = { "Jennifer", "Haru" };
  Accident accident_1;
  Accident accident_2;
  accident_1.year = 2007;
  accident_1.owner = "Haru";
  accident_1.loss_of_value = 1023.5;
  accident_2.year = 2009;
  accident_2.owner = "Jennifer";
  accident_2.loss_of_value = 636.2;
  my_car.most_recent_accident = accident_1;
  my_car.features["seats"] = 7;
  my_car.features["trunk_space"] = 10;
  std::ofstream fout;
  fout.open("test.s");
  fout << my_car;
  fout.close();
  Car your_car;
  std::ifstream fin;
  fin.open("test.s");
  fin >> your_car;
  fin.close();
  std::cout << "Color: " << your_car.color << std::endl;
  std::cout << "Mileage: " << your_car.mileage << std::endl;
  std::cout << "Owners: " << your_car.owners << std::endl;
  std::cout << "Accident: " << your_car.most_recent_accident << std::endl;
  std::cout << "Features: " << your_car.features << std::endl;
  return 0;
}
