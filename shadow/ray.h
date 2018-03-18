#ifndef SHADOW_RAY
#define SHADOW_RAY

#include "shadow/vector.h"
#include "aqua/serializable.h"

namespace shadow {

// Ray
struct Ray : public aqua::Serializable {
  Ray();
  Ray(const Vector& a, const Vector& b);
  void Print();
  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
  Vector direction;
  Vector source;
};

}  // namespace shadow

#endif
