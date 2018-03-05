#include "shadow.h"
#include <math.h>

/****************************************************************
 * Math Operations
*****************************************************************/

namespace shadow {

float Cotangent(float angle) {
  return (float)(1.0 / tan(angle));
}

float DegreesToRadians(float degrees) {
  return degrees * (float)(PI / 180);
}

float RadiansToDegrees(float radians) {
  return radians * (float)(180 / PI);
}

}  // namespace shadow
