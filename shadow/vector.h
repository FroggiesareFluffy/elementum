#ifndef SHADOW_VECTOR
#define SHADOW_VECTOR

#include <iostream>
#include <fstream>

#include "aqua/serializable.h"

namespace shadow {

struct Ray;
struct Plane;
  
struct Vector : public aqua::Serializable
{
 public:
  float data[4];
  float& x;
  float& y;
  float& z;
  float& w;
  float& r;
  float& g;
  float& b;
  float& a;
  Vector();
  Vector(float, float, float, float);
  Vector(const Vector& right);
  Vector& operator = (const Vector& right);
  void Set(float, float, float, float);
  float& operator[] (int);
  float& operator[] (int) const;
  void Print() const;
  void Zero();
  void Normalize();
  float Dot(const Vector& v) const;
  Vector Cross(const Vector& v) const;
  float DistanceTo(const Vector& v) const;
  float Magnitude() const;
  float Length() const; // alias
  float Angle(const Vector& v) const;
  float Cos(const Vector& v) const;
  float Sin(const Vector& v) const;
  void Round();
  void ProjectOnto(const Vector& v);
  void ProjectOnto(const Ray& r);
  void ProjectOnto(const Plane& p);
  Vector& operator = (float c);
  Vector& operator += (const Vector& v);
  Vector& operator -= (const Vector& v);
  Vector& operator *= (float c);
  Vector& operator /= (float c);
  bool operator == (float c) const;
  bool operator == (const Vector& v) const;
  bool operator != (const Vector& v) const;
  void Serialize(std::ostream& os) const override;
  void Unserialize(std::istream& is) override;
};

Vector operator + (const Vector& v1, const Vector& v2);
Vector operator - (const Vector& v1, const Vector& v2);
Vector operator * (const Vector&  v, float c);          // scalar
Vector operator / (const Vector&  v, float c);          // scalar
float  operator * (const Vector& v1, const Vector& v2); // Dot Product
Vector operator ^ (const Vector& v1, const Vector& v2); // Cross Product

bool operator <  (const Vector& v1, const Vector& v2);

}  // namespace shadow

std::ostream& operator << (std::ostream& out, const shadow::Vector& v);
std::istream& operator >> (std::istream& in, shadow::Vector& v);

#endif


