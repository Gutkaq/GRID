#include "../math/zi/zi_matrix.h"
#include <cassert>
#include <iostream>

int main() {
    Zi z = Zi(3, 4);
    ZiMatrix M = ZiMatrix::from_zi(z);

    std::cout << "M from 3+4i = [[ " << M.m[0][0] << ", " << M.m[0][1] << " ], [ " << M.m[1][0] << ", " << M.m[1][1] << " ]]\n";

    assert(M.m[0][0] == 3 && M.m[0][1] == -4 && M.m[1][0] == 4 && M.m[1][1] == 3);
    std::cout << "PASS: ZiMatrix from Zi\n";

    return 0;
}
