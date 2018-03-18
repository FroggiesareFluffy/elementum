#include "shadow/ray.h"
#include "shadow/plane.h"
#include "shadow/vector.h"

namespace shadow {

// Plane
Plane::Plane() {};

Plane::Plane(const Vector& a, const Vector& b, const Vector& c){
  Ray r1(a, b);
  Ray r2(a, c);
  normal = r1.direction.Cross(r2.direction);
  normal.Normalize();
  point_on_plane = a;
}
  
Plane::Plane(const Ray& ray1, const Ray& ray2){
  normal = ray1.direction.Cross(ray2.direction);
  normal.Normalize();
  point_on_plane = ray1.source;
}
  
float Plane::AngleToPoint(const Vector& p) const {
  Vector direction = point_on_plane - p;
  return direction.Dot(normal);
}
bool Plane::Coplanar(const Vector& p) const {
  return AngleToPoint(p) == 0;
}
bool Plane::SameSide(const Vector& p1, const Vector& p2) const {
  float a1 = AngleToPoint(p1);
  float a2 = AngleToPoint(p2);
  return (a1 < 0) ? a2 < 0 : (a1 > 0) ? a2 > 0 : false; // on line
}
void Plane::Print() const {
  std::cout << "Normal: ";
  normal.Print();
  std::cout << "Point on Plane: ";
  point_on_plane.Print();
}
Vector Plane::Intercept(const Ray& ray) const {
  float denominator = ray.direction.Dot(normal);
  if (denominator == 0)
    std::cout << "Division by 0 imminent. Plane & Line are parallel\n";
  Vector t = point_on_plane - ray.source;
  float scalar = t.Dot(normal) / denominator;
  Vector intercept_pt = ray.direction;
  intercept_pt = intercept_pt * scalar;
  intercept_pt = intercept_pt + ray.source;
  return intercept_pt;
}
Vector Plane::Intercept(const Vector& p1, const Vector& p2) const {
  Ray r(p1, p2);
  return Intercept(r);
}

void Plane::Serialize(std::ostream& os) const {
  os << normal << " " << point_on_plane;
}

void Plane::Unserialize(std::istream& is) {
  is >> normal >> point_on_plane;
}

}  // namespace shadow
