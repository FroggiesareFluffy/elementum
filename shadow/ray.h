#ifndef SHADOW_RAY
#define SHADOW_RAY

#include "shadow/vector.h"

namespace shadow {

// Ray
struct Ray {
  Ray();
  Ray(const Vector& a, const Vector& b);
  void Print();
  Vector direction;
  Vector source;
};

}  // namespace shadow

#endif
