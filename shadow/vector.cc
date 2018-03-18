/*****************************************************************
 *                         Vector                            *
 *****************************************************************/
#include "shadow/shadow.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "shadow/vector.h"
#include "shadow/plane.h"
#include "shadow/ray.h"

namespace shadow {

/************************** Constructor **************************/
Vector::Vector() :
  x(data[0]), y(data[1]), z(data[2]), w(data[3]),
  r(data[0]), g(data[1]), b(data[2]), a(data[3]) {
  data[0] = 0;
  data[1] = 0;
  data[2] = 0;
  data[3] = 1;
}

/************************** Constructor **************************/
Vector::Vector(float p_x, float p_y, float p_z, float p_w) :
  x(data[0]), y(data[1]), z(data[2]), w(data[3]),
  r(data[0]), g(data[1]), b(data[2]), a(data[3]) {
  x = p_x;
  y = p_y;
  z = p_z;
  w = p_w;
}

/************************** Constructor **************************/
Vector::Vector(const Vector& right) :
  x(data[0]), y(data[1]), z(data[2]), w(data[3]),
  r(data[0]), g(data[1]), b(data[2]), a(data[3]) {
  for (int i = 0; i < 4; ++i) data[i] = right.data[i];
}

/********************** Assignment Operator **********************/
Vector& Vector::operator = (const Vector& right) {
  for (int i = 0; i < 4; ++i) data[i] = right.data[i];
}

/************************** Index Vector *************************/
float& Vector::operator [] (int index) {
  switch (index) {
  case 0: return x;
  case 1: return y;
  case 2: return z;
  default: return w;
  }
}

/*************************** Set Vector **************************/
void Vector::Set(float p_x, float p_y, float p_z, float p_w) {
  x = p_x;
  y = p_y;
  z = p_z;
  w = p_w;
}

/****************************** Zero *****************************/
void Vector::Zero() {
  x = 0;
  y = 0;
  z = 0;
  w = 1;
}

/**************************** Normalize **************************/
void Vector::Normalize() {
  float mag = Magnitude();
  if (mag != 0) {
    x /= mag;
    y /= mag;
    z /= mag;
    w = 1;
  }
}

/*************************** Dot Product *************************/
float Vector::Dot(const Vector& v) const {
  return (x * v.x) + (y * v.y) + (z * v.z);
}

/************************** Cross Product ************************/
Vector Vector::Cross(const Vector& v) const {
  return Vector((y * v.z) - (z * v.y),
		(z * v.x) - (x * v.z),
		(x * v.y) - (y * v.x), 
		1);
}

/*********************** Distance to Vector **********************/
float Vector::DistanceTo(const Vector& v) const {
  float dx = v.x - x;
  float dy = v.y - y;
  float dz = v.z - z;
  return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

/***************************** Length ****************************/
float Vector::Length() const {
  return sqrt((x * x) + (y * y) + (z * z));
}

/**************************** Magnitude **************************/
float Vector::Magnitude() const {
  return Length();
}

/*************************** Assignment **************************/
Vector& Vector::operator = (float c) {
  x = c;
  y = c;
  z = c;
  w = 1;
  return *this;
}

/************************** Plus Equals **************************/
Vector& Vector::operator += (const Vector& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

/************************** Minus Equals *************************/
Vector& Vector::operator -= (const Vector& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

/************************** Times Equals *************************/
Vector& Vector::operator *= (float c) {
  x *= c;
  y *= c;
  z *= c;
  return *this;
}

/************************** Divide Equals ************************/
Vector& Vector::operator /= (float c) {
  x /= c;
  y /= c;
  z /= c;
  return *this;
}

/****************************** Print ****************************/
void Vector::Print() const {
  std::cout << *this;
}

/************************** Round Helper *************************/
void RoundFloat(float* x, int precision) {
  float temp = *x * pow(10.0, precision);
  temp = temp < 0 ? ceil(temp - 0.5) : floor(temp + 0.5);
  *x = temp / pow(10.0, precision);
}

/****************************** Round ****************************/
void Vector::Round() {
  RoundFloat(&x, 3);
  RoundFloat(&y, 3);
  RoundFloat(&z, 3);
  RoundFloat(&w, 3);
}

/****************************** Sine *****************************/
float Vector::Sin(const Vector& p_v) const {
  Vector a = *this;
  Vector v = p_v;
  a.Normalize();
  v.Normalize();
  return (a.Cross(v)).Magnitude();
}

/***************************** Cosine ****************************/
float Vector::Cos(const Vector& p_v) const {
  Vector a = *this;
  Vector v = p_v;
  a.Normalize();
  v.Normalize();
  return a.Dot(v);
}

/*********************** Project Onto Vector **********************/
void Vector::ProjectOnto(const Vector& v) {
  // Project onto vector (the closest point) on vector
  // to current point
  float scalar = Dot(v) / pow(v.Magnitude(), 2);
  *this = (v * scalar);
}

/************************ Project Onto Ray ************************/
void Vector::ProjectOnto(const Ray& r) {
  // Project onto the ray (the closest point) on ray
  // to current point

  Vector offset = r.source;
  *this -= offset;
  ProjectOnto(r.direction);
  *this += offset;
}

/*********************** Project Onto Plane ***********************/
void Vector::ProjectOnto(const Plane& p) {
  Vector offset = p.point_on_plane;
  *this -= p.point_on_plane;
  float scalar = (Dot(p.normal)/pow(p.normal.Magnitude(), 2));
  *this -= (p.normal * scalar);
  *this += p.point_on_plane;
}

/****************************** Angle ****************************/
float Vector::Angle(const Vector& v) const {
  return RadiansToDegrees(acos(Cos(v)));
}

/********************** Comparison to Float **********************/
bool Vector::operator == (float c) const {
  // Ignore w (for now)
  return (x == c && y == c && z == c);
}

/********************** Comparison to Vector *********************/
bool Vector::operator == (const Vector& p_v) const {
  // Ignore w (for now)
  Vector temp = *this;
  temp.Round();
  Vector v = p_v;
  v.Round();
  return (temp.x == v.x && temp.y == v.y && temp.z == v.z);
}

/********************** Comparison to Vector *********************/
bool Vector::operator != (const Vector& p_v) const {
  return !(*this == p_v);
}

/************************* Plus Operator *************************/
Vector operator + (const Vector& v1_p, const Vector& v2) {
  Vector v1 = v1_p;
  v1 += v2;
  return v1;
}

/************************* Minus Operator ************************/
Vector operator - (const Vector& v1_p, const Vector& v2) {
  Vector v1 = v1_p;
  v1 -= v2;
  return v1;
}

/********************** Dot Product Operator *********************/
float operator * (const Vector& v1, const Vector& v2) {
  return v1.Dot(v2);
}

/********************* Cross Product Operator ********************/
Vector operator ^ (const Vector& v1, const Vector& v2) {
  return v1.Cross(v2);
}

/************************* Times Operator ************************/
Vector operator * (const Vector& p_v, float c) {
  Vector v = p_v;
  v *= c;
  return v;
}

/************************ Divide Operator ************************/
Vector operator / (const Vector& p_v, float c) {
  Vector v = p_v;
  v /= c;
  return v;
}

/************************ Allows Sorting ************************/
bool operator < (const Vector& v1, const Vector& v2) {
  if (v1.x < v2.x) return true;
  if (v1.x > v2.x) return false;
  if (v1.y < v2.y) return true;
  if (v1.y > v2.y) return false;
  if (v1.z < v2.z) return true;
  return false;
}

/************************ Serialization *************************/

void Vector::Serialize(std::ostream& os) const {
  os << r << " " << g << " " << b << " " << a;
}

void Vector::Unserialize(std::istream& is) {
  is >> r >> g >> b >> a;
}

}  // namespace shadow

std::ostream& operator << (std::ostream& out, const shadow::Vector& v) {
  out << "[ " << v.x << " " << v.y << " "
      << v.z << " " << v.w << " ]";
  return out;
}

std::istream& operator >> (std::istream& in, shadow::Vector& v) {
  std::string trash;
  in >> trash; // [
  in >> v.x >> v.y >> v.z >> v.w;
  in >> trash; // ]
  return in;
}
