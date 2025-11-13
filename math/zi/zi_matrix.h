#ifndef ZI_MATRIX_H
#define ZI_MATRIX_H

#include <cstdint>

#include "zi.h"

struct ZiMatrix {
  int32_t m[2][2];

  ZiMatrix(int32_t a = 0, int32_t b = 0);

  static ZiMatrix from_zi(const Zi& z);
};

#endif //ZI_MATIX_H
