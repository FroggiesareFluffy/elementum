#ifndef SHADOW_MATRIX
#define SHADOW_MATRIX

#include "aqua/serializable.h"

namespace shadow {

struct Ray;
struct Plane;
struct Vector;
  
class Matrix : public aqua::Serializable{
 public:
  Matrix();  // Identity Matrix
  Matrix(float, float, float, float,
	 float, float, float, float,
	 float, float, float, float,
	 float, float, float, float);
  Matrix& operator = (const Matrix& right);
  Matrix(const Matrix& right);
  void Transpose();
  Matrix Inverse() const;
  void Invert();
  float* operator [] (int);  // row column order
  const float* operator [] (int) const;
  float Determinant() const;
  void Print() const;
  void Clear();  // Reset to Identity Matrix
  void operator += (const Matrix&);
  void operator -= (const Matrix&);
  void operator *= (const Matrix&);
  void PostMultiply(const Matrix&);
  void operator *= (const Vector&);
  void operator *= (float);
  void operator /= (float);
  static Matrix XRotationMatrix(float angle);
  static Matrix YRotationMatrix(float angle);
  static Matrix ZRotationMatrix(float angle);
  static Matrix RotationMatrix(const Vector& axis,
			       float sine, float cosine);
  static Matrix RotationMatrix(const Ray& ray, float sine, float cosine);
  static Matrix ScaleMatrix(float, float, float);
  static Matrix ScaleMatrix(float);
  static Matrix TranslationMatrix(float, float, float);
  static Matrix ProjectionMatrix(float fov, float aspect_ratio,
				 float near, float far);
  void Rotate(const Ray&, float, float);
  void Serialize(std::ostream& os) const;
  void Unserialize(std::istream& is);
  float m[16];  // Row Major Order
 private:
  void Inversion(Matrix* temp, int order) const;
  int GetMinor(Matrix* temp, int row, int column, int order) const;
  float Determinant(int order) const;  // Recursive
};

Matrix operator + (const Matrix& m1, const Matrix& m2);
Matrix operator - (const Matrix& m1, const Matrix& m2);
Matrix operator * (const Matrix& m1, const Matrix& m2);
Matrix operator * (const Matrix& m, float c);
Matrix operator / (const Matrix& m, float c);
Matrix operator * (float c, const Matrix& m);
Vector operator * (const Matrix& m, const Vector& v);
   
}  // namespace shadow

#endif
