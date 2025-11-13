#include "zi_matrix.h"

ZiMatrix::ZiMatrix(int32_t a, int32_t b) {
  m[0][0] = a;
  m[0][1] = -b;
  m[1][0] = b;
  m[1][1] = a;
}

ZiMatrix ZiMatrix::from_zi(const Zi& z) {
  return ZiMatrix(z.a, z.b);
}
