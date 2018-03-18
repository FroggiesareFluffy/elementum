#include "shadow/shadow.h"
#include "shadow/matrix.h"
#include "shadow/vector.h"
#include "shadow/ray.h"
#include "shadow/plane.h"
#include <cmath>
#include <iostream>

namespace shadow {

/************************** Constructor ************************/
Matrix::Matrix() {
  Clear();
}

/************************** Constructor ************************/
Matrix::Matrix(float a, float b, float c, float d,
	       float e, float f, float g, float h,
	       float i, float j, float k, float l,
	       float n, float o, float p, float q) {
  m[0] = a; m[1] = b; m[2] = c; m[3] = d;
  m[4] = e; m[5] = f; m[6] = g; m[7] = h;
  m[8] = i; m[9] = j; m[10] = k; m[11] = l;
  m[12] = n; m[13] = o; m[14] = p; m[15] = q;
}

/************************ Copy Constructor *********************/
Matrix::Matrix(const Matrix& right) {
  for (int i = 0; i < 16; ++i) m[i] = right.m[i];
}

/*********************** Assignment Operator *******************/
Matrix& Matrix::operator = (const Matrix& right) {
  for (int i = 0; i < 16; ++i) m[i] = right.m[i]; 
}


/*********************** Transpose Matrix **********************/
void Matrix::Transpose() {
  float temp;
  for (int i = 0; i < 4; i++){
    for (int j = i; j < 4; j++){
      temp = m[(i * 4) + j];
      m[(i * 4) + j] = m[(j * 4) + i];
      m[(j * 4) + i] = temp;
    }
  }
}


/********************* Access like 2D array *********************/
float* Matrix::operator[](int index) {
  return &(m[4 * index]);
}

/********************* Access like 2D array *********************/
const float* Matrix::operator[](int index) const {
  return &(m[4 * index]);
}

/*************************** Determinant ************************/
float Matrix::Determinant() const {
  Matrix partial;
  double det = 1.0/partial.Determinant(4);
  return det;
}

/*************************** Get Inverse *************************/
Matrix Matrix::Inverse() const {
  Matrix inv_mat;
  Inversion(&inv_mat, 4);
  return inv_mat;
}

/************************** Invert Matrix ************************/
void Matrix::Invert() {
  Inversion(this, 4);
}

/*************************** Print Matrix ************************/
void Matrix::Print() const {
  std::cout << *this;
}

/************************ Clear to Identity **********************/
void Matrix::Clear() {
  // Identity Matrix
  m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
  m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
  m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
  m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

/*********************** Get Inverse Helper **********************/
void Matrix::Inversion(Matrix* Y, int order) const {
  // get the determinant of a
  double det = 1.0/Determinant(order);

  Matrix minor;

  for(int j=0;j<order;++j) {
      for(int i=0;i<order;++i) {
	// get the co-factor (matrix) of m(j,i)
	GetMinor(&minor,j,i,order);
	(*Y)[i][j] = det*minor.Determinant(order-1);
	if((i+j)%2 == 1)
	  (*Y)[i][j] = -(*Y)[i][j];
      }
  }
}


// calculate the cofactor of element (row,col)
/*************************** Get Minor *************************/
int Matrix::GetMinor(Matrix* dest, int row, int col, int order) const {
  // indicate which col and row is being copied to dest
  int column_count=0,row_count=0;

  for(int i = 0; i < order; ++i) {
    if(i != row) {
      column_count = 0;
      for(int j = 0; j < order; ++j) {
	// when j is not the element
	if(j != col) {
	  (*dest)[row_count][column_count] = (*this)[i][j];
	  column_count++;
	}
      }
      row_count++;
    }
  }

  return 1;
}

/************************ Determinant Helper **********************/
float Matrix::Determinant(int order) const {
  // order must be >= 0
  // stop the recursion when matrix is a single element
  if (order == 1) return (*this)[0][0];

  // the determinant value
  float det = 0;

  // allocate the cofactor matrix
  Matrix minor;
  
  for (int i = 0; i < order; ++i) {
    // get minor of element (0,i)
    GetMinor(&minor, 0, i , order);
    
    // the recusion is here!
    det+=(i%2==1?-1.0:1.0)*(*this)[0][i]*minor.Determinant(order-1);
  }

  return det;
}

/*************************** Add Matrix *************************/
void Matrix::operator += (const Matrix& right) {
  for (int i = 0; i < 16; ++i) m[i] += right.m[i];
}

/************************* Subtract Matrix **********************/
void Matrix::operator -= (const Matrix& right) {
  for (int i = 0; i < 16; ++i) m[i] -= right.m[i];
}

/************************ Multiply Matrix ***********************/
void Matrix::operator *= (const Matrix& right) {
  Matrix out;

  for (int row = 0; row < 4; ++row){
    for (int column = 0; column < 4; ++column){
      out[row][column] =
	(((*this)[row][0] * right[0][column]) +
	 ((*this)[row][1] * right[1][column]) +
	 ((*this)[row][2] * right[2][column]) +
	 ((*this)[row][3] * right[3][column]));
    }
  }
  *this = out;
}

void Matrix::PostMultiply(const Matrix& right) {
  Matrix out;

  for (int row = 0; row < 4; ++row){
    for (int column = 0; column < 4; ++column){
      out[row][column] =
	((right[row][0] * (*this)[0][column]) +
	 (right[row][1] * (*this)[1][column]) +
	 (right[row][2] * (*this)[2][column]) +
	 (right[row][3] * (*this)[3][column]));
    }
  }
  *this = out;
}

/*********************** Multiply Constant **********************/
void Matrix::operator *= (float c) {
  for (int i = 0; i < 16; ++i) m[i] *= c;
}

/************************ Divide Constant ***********************/
void Matrix::operator /= (float c) {
  for (int i = 0; i < 16; ++i) m[i] /= c;
}

bool Matrix::operator == (const Matrix& right) const {
  for (int i = 0; i < 16; ++i)
    if (m[i] != right.m[i]) return false;
  return true;
}

/***************************** Rotate *****************************/
Matrix Matrix::XRotationMatrix(float angle) {
  Matrix rotation_matrix;
  angle = DegreesToRadians(angle);
  float sin_x = (float)sin(angle);
  float cos_x = (float)cos(angle);
  rotation_matrix[1][1] = cos_x;
  rotation_matrix[1][2] = -sin_x;
  rotation_matrix[2][1] = sin_x;
  rotation_matrix[2][2] = cos_x;
  return rotation_matrix;
}

Matrix Matrix::YRotationMatrix(float angle) {
  Matrix rotation_matrix;
  angle = DegreesToRadians(angle);
  float sin_y = (float)sin(angle);
  float cos_y = (float)cos(angle);
  rotation_matrix[0][0] = cos_y;
  rotation_matrix[0][2] = sin_y;
  rotation_matrix[2][0] = -sin_y;
  rotation_matrix[2][2] = cos_y;
  return rotation_matrix;
}
  
Matrix Matrix::ZRotationMatrix(float angle) {
  Matrix rotation_matrix;
  angle = DegreesToRadians(angle);
  float sin_z = (float)sin(angle);
  float cos_z = (float)cos(angle);
  rotation_matrix[0][0] = cos_z;
  rotation_matrix[0][1] = -sin_z;
  rotation_matrix[1][0] = sin_z;
  rotation_matrix[1][1] = cos_z;
  return rotation_matrix;
}

/**************************** Rotate ******************************/
Matrix Matrix::RotationMatrix(const Vector& p_axis,
			      float sine, float cosine) {
  Matrix rotation_matrix;
  // See inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
  Vector axis = p_axis;
  axis.Normalize();
  float u, v, w;
  u = axis.x;
  v = axis.y;
  w = axis.z;
  float u2 = u * u;
  float v2 = v * v;
  float w2 = w * w;
  float uv = u * v;
  float uw = u * w;
  float vw = v * w;
  float oMC = 1 - cosine;
  Matrix R;
  // TODO - Check that these are being accessed in row-column order
  R[0][0] = u2 + ((1 - u2) * cosine);
  R[0][1] = (uv * oMC) - (w * sine);
  R[0][2] = (uw * oMC) + (v * sine);
  
  R[1][0] = (uv * oMC) + (w * sine);
  R[1][1] = v2 + ((1 - v2) * cosine);
  R[1][2] = (vw * oMC) - (u * sine);

  R[2][0] = (uw * oMC) - (v * sine);
  R[2][1] = (vw * oMC) + (u * sine);
  R[2][2] = w2 + ((1 - w2) * cosine);

  rotation_matrix.PostMultiply(R);
  return rotation_matrix;
}

/**************************** Rotate ******************************/
Matrix Matrix::RotationMatrix(const Ray& p_ray, float sine, float cosine)
{
  Matrix rotation_matrix;
  Ray ray = p_ray;
  // See inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
  float a = ray.source.x;
  float b = ray.source.y;
  float c = ray.source.z;
  ray.direction.Normalize();
  float u = ray.direction.x;
  float v = ray.direction.y;
  float w = ray.direction.z;
  float u2 = u * u;
  float v2 = v * v;
  float w2 = w * w;
  float uv = u * v;
  float uw = u * w;
  float vw = v * w;
  float oMC = 1 - cosine;
  float usin = u * sine;
  float vsin = v * sine;
  float wsin = w * sine;
  float au = a * u;
  float av = a * v;
  float aw = a * w;
  float bu = b * u;
  float bv = b * v;
  float bw = b * w;
  float cu = c * u;
  float cv = c * v;
  float cw = c * w;
  Matrix R;
  
  R[0][0] = u2 + ((v2 + w2) * cosine);
  R[0][1] = (uv * oMC) - wsin;
  R[0][2] = (uw * oMC) + vsin;
  R[0][3] = (((a * (v2 + w2)) - (u * (bv + cw))) * oMC) + ((bw - cv) * sine);

  R[1][0] = (uv * oMC) + wsin;
  R[1][1] = v2 + ((u2 + w2) * cosine);
  R[1][2] = (vw * oMC) - usin;
  R[1][3] = (((b * (u2 + w2)) - (v * (au + cw))) * oMC) + ((cu - aw) * sine);

  R[2][0] = (uw * oMC) - vsin;
  R[2][1] = (vw * oMC) + usin;
  R[2][2] = w2 + ((u2 + v2) * cosine);
  R[2][3] = (((c * (u2 + v2)) - (w * (au + bv))) * oMC) + ((av - bu) * sine);
  
  rotation_matrix.PostMultiply(R);
  return rotation_matrix;
}

/***************************** Scale ******************************/
Matrix Matrix::ScaleMatrix(float size) {
  return ScaleMatrix(size, size, size);
}

/***************************** Scale ******************************/
Matrix Matrix::ScaleMatrix(float x, float y, float z) {
  Matrix scale_matrix;

  scale_matrix[0][0] = x;
  scale_matrix[1][1] = y;
  scale_matrix[2][2] = z;

  return scale_matrix;
}

/**************************** Transate ****************************/
Matrix Matrix::TranslationMatrix(float x, float y, float z) {
  Matrix translation_matrix;
    
  translation_matrix[0][3] = x;
  translation_matrix[1][3] = y;
  translation_matrix[2][3] = z;

  return translation_matrix;
}

/**************************** Project *****************************/
Matrix Matrix::ProjectionMatrix(float field_of_view, float aspect_ratio,
				float near, float far) {
  // This may need to change -alternate
  
  Matrix projection_matrix;
  
  float y_scale, x_scale, frustum_length;
  y_scale = Cotangent(DegreesToRadians(field_of_view / 2));
  x_scale = y_scale / aspect_ratio;
  frustum_length = far - near;

  projection_matrix[0][0]  = x_scale;
  projection_matrix[1][1]  = y_scale;
  projection_matrix[2][2] = -((far + near) / frustum_length);
  projection_matrix[3][2] = -1;
  projection_matrix[2][3] = -((2 * near * far) / frustum_length);

  return projection_matrix;
}

/*************************** Add Matrix *************************/
Matrix operator + (const Matrix& m1, const Matrix& m2) {
  Matrix sum;
  for (int i = 0; i < 16; ++i) sum.m[i] = m1.m[i] + m2.m[i];
  return sum;
}

/************************ Subtract Matrix ***********************/
Matrix operator - (const Matrix& m1, const Matrix& m2) {
  Matrix dif;
  for (int i = 0; i < 16; ++i) dif.m[i] = m1.m[i] - m2.m[i];
  return dif;
}

/************************ Multiply Matrix ***********************/
Matrix operator * (const Matrix& m1, const Matrix& m2) {
  Matrix product = m1;
  product *= m2;
  return product;
}

/*********************** Multiply Constant **********************/
Matrix operator * (const Matrix& m, float c) {
  Matrix product = m;
  for (int i = 0; i < 16; ++i) product.m[i] *= c;
  return product;
}

/*********************** Multiply Constant **********************/
Matrix operator * (float c, const Matrix& m) {
  Matrix product = m;
  for (int i = 0; i < 16; ++i) product.m[i] *= c;
  return product;
}

/************************ Divide Constant ***********************/
Matrix operator / (const Matrix& m, float c) {
  Matrix product = m;
  for (int i = 0; i < 16; ++i) product.m[i] /= c;
  return product;
}

/************************ Multiply Vector ***********************/
Vector operator * (const Matrix& m, const Vector& v) {
  return Vector((m[0][0] * v.x) + (m[0][1] * v.y) + 
		(m[0][2] * v.z) + (m[0][3] * v.w),
		(m[1][0] * v.x) + (m[1][1] * v.y) + 
		(m[1][2] * v.z) + (m[1][3] * v.w),
		(m[2][0] * v.x) + (m[2][1] * v.y) + 
		(m[2][2] * v.z) + (m[2][3] * v.w),
		(m[3][0] * v.x) + (m[3][1] * v.y) + 
		(m[3][2] * v.z) + (m[3][3] * v.w));
}

void Matrix::Serialize(std::ostream& os) const override {
  for (int i = 0; i < 16; i++) {
    os << m[i] << " ";
  }
}

void Matrix::Unserialize(std::istream& is) override {
  for (int i = 0; i < 16; i++) {
    is >> m[i];
  }
}
  
}  // namespace shadow
