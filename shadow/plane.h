#ifndef SHADOW_PLANE
#define SHADOW_PLANE

#include "shadow/vector.h"

namespace shadow {

struct Ray;

// Plane
struct Plane {
  Plane();
  Plane(const Vector& a, const Vector& b, const Vector& c);
  Plane(const Ray& ray1, const Ray& ray2);
  float AngleToPoint(const Vector& p) const;
  bool Coplanar(const Vector& p) const;
  bool SameSide(const Vector& p1, const Vector& p2) const;
  void Print() const;
  Vector Intercept(const Ray& ray) const;
  Vector Intercept(const Vector& p1, const Vector& p2) const;
  Vector normal;
  Vector point_on_plane; 
};

}  // namespace shadow
 
#endif
