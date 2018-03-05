#include "shadow/ray.h"
#include "shadow/vector.h"
#include <iostream>

namespace shadow {

// Ray
Ray::Ray() {};
Ray::Ray(const Vector& a, const Vector& b){
  direction = b - a;
  direction.Normalize();
  source = a;
}
void Ray::Print(){
  std::cout << "Direction: ";
  direction.Print();
  std::cout << "Source: ";
  source.Print();
}

}  // namespace shadow
