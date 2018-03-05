#include "shadow/matrix.h"
#include "shadow/vector.h"


int main(int argc, char** argv) {
  shadow::Vector z_positive(0, 0, 1, 1);
  shadow::Vector z_negative(0, 0, -1, 1);
  auto y_rotation_matrix = shadow::Matrix::YRotationMatrix(180);
  z_positive = y_rotation_matrix * z_positive;
  if (z_positive != z_negative) {
    std::cout << "Fail: ";
    z_positive.Print();
    std::cout << " != ";
    z_negative.Print();
  } else {
    std::cout << "Pass\n";
  }
  return 0;
}
