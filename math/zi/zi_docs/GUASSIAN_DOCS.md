Gaussian Integers (Zi) Module - Architecture Documentation
Version: 1.0
Module Path: math/zi/
Last Updated: 2025-11-14

Module Overview
The Zi module implements Gaussian integer arithmetic for the GRID computational mathematics library. Gaussian integers form a Euclidean domain 
Z
[
i
]
Z[i] supporting algebraic operations, Euclidean division, and GCD algorithms.​​

Type Hierarchy
Core Types
cpp
// Primary algebraic type
struct Zi {
    int32_t a;  ///< Real component
    int32_t b;  ///< Imaginary component (coefficient of i)
};

// Result types
struct DivResult {
    Zi q;       ///< Quotient
    Zi r;       ///< Remainder with N(r) < N(divisor)
};

struct XgcdResult {
    Zi g;       ///< GCD of inputs
    Zi s;       ///< Bézout coefficient for first input
    Zi t;       ///< Bézout coefficient for second input
};
Matrix Representation
cpp
struct ZiMatrix {
    int32_t m[2][2];  ///< 2×2 matrix encoding Gaussian integer
};
Encoding: 
a
+
b
i
↦
(
a
−
b
b
a
)
a+bi↦( 
a
b
  
−b
a
 )

Type Dependencies
text
Zi (base type)
├── DivResult (depends on Zi)
├── XgcdResult (depends on Zi)
└── ZiMatrix (isomorphic to Zi)

ZiProperties (namespace)
└── depends on Zi, DivResult, XgcdResult
API Reference
Constructors
cpp
Zi::Zi()
Description: Default constructor, initializes to zero
Postcondition: a == 0 && b == 0

cpp
Zi::Zi(int32_t real, int32_t imag)
Description: Parameterized constructor
Parameters:

real: Real component

imag: Imaginary component
Postcondition: a == real && b == imag

Member Methods
Equality and Comparison
cpp
bool Zi::eq(const Zi& other) const
Description: Tests equality of two Gaussian integers
Parameters: other - Right-hand operand
Returns: true if a == other.a && b == other.b
Complexity: O(1)

cpp
bool Zi::isZero() const
Description: Tests if element equals zero
Returns: true if a == 0 && b == 0
Complexity: O(1)

cpp
bool Zi::isUnit() const
Description: Tests if element is a unit (±1, ±i)
Returns: true if norm() == 1
Complexity: O(1)

cpp
bool Zi::isAssociate(const Zi& other) const
Description: Tests if two elements differ by a unit factor
Mathematical Property: 
a
∼
b
  
⟺
  
∃
u
∈
U
:
a
=
u
b
a∼b⟺∃u∈U:a=ub
Returns: true if this and other are associates
Complexity: O(1)

Arithmetic Operations
cpp
Zi Zi::add(const Zi& other) const
Description: Computes sum of two Gaussian integers
Parameters: other - Addend
Returns: New Zi representing (a + other.a) + i(b + other.b)
Properties: Commutative, associative
Complexity: O(1)

cpp
Zi Zi::sub(const Zi& other) const
Description: Computes difference of two Gaussian integers
Parameters: other - Subtrahend
Returns: New Zi representing (a - other.a) + i(b - other.b)
Complexity: O(1)

cpp
Zi Zi::mul(const Zi& other) const
Description: Computes product using complex multiplication
Parameters: other - Multiplicand
Returns: New Zi where result.a = a*other.a - b*other.b, result.b = a*other.b + b*other.a
Properties: Commutative, associative, distributes over addition
Complexity: O(1)
Overflow Note: Intermediate values use int32_t arithmetic; ensure inputs bounded

cpp
Zi Zi::conj() const
Description: Computes complex conjugate
Returns: New Zi representing a - bi
Properties: Involution conj(conj(z)) == z, respects addition and multiplication
Complexity: O(1)

cpp
int64_t Zi::norm() const
Description: Computes field norm (sum of squares)
Returns: 
a
2
+
b
2
a 
2
 +b 
2
  as int64_t
Properties: Multiplicative N(zw) = N(z)N(w), non-negative
Complexity: O(1)
Overflow Safety: Uses int64_t to handle int32_t squares

Global Constants
cpp
extern const Zi ZERO;  // 0 + 0i
extern const Zi ONE;   // 1 + 0i
extern const Zi I;     // 0 + 1i
Description: Predefined constant Gaussian integers
Linkage: External, defined in zi.cpp

Free Functions
Division Algorithm
cpp
DivResult divEuclid(const Zi& a, const Zi& b)
Description: Euclidean division with minimal remainder
Parameters:

a - Dividend

b - Divisor (must be non-zero)
Returns: DivResult{q, r} satisfying:

a
=
b
q
+
r
a=bq+r

N
(
r
)
<
N
(
b
)
N(r)<N(b)
Algorithm: Computes 
q
=
round
(
a
/
b
)
q=round(a/b) in complex plane, then 
r
=
a
−
b
q
r=a−bq
Precondition: !b.isZero()
Postcondition: a.eq(b.mul(result.q).add(result.r)) and result.r.norm() < b.norm()
Complexity: O(1)

GCD Algorithms
cpp
Zi gcd(const Zi& a, const Zi& b)
Description: Computes greatest common divisor using Euclidean algorithm
Parameters: a, b - Input Gaussian integers
Returns: GCD of a and b (unique up to units)
Algorithm: Iterative Euclidean algorithm with divEuclid
Properties:

gcd(a, b) divides both a and b

Any common divisor of a and b divides gcd(a, b)
Special Cases:

gcd(0, z) == z

gcd(z, z) ~ z
Complexity: O(log min(N(a), N(b)))

cpp
XgcdResult xgcd(const Zi& a, const Zi& b)
Description: Extended Euclidean algorithm computing Bézout coefficients
Parameters: a, b - Input Gaussian integers
Returns: XgcdResult{g, s, t} satisfying:

g == gcd(a, b)

g.eq(s.mul(a).add(t.mul(b))) (Bézout's identity)
Algorithm: Extended Euclidean algorithm tracking coefficients
Use Case: Computing modular inverses, solving linear Diophantine equations
Complexity: O(log min(N(a), N(b)))

Property Verification (Testing Namespace)
cpp
namespace ZiProperties {
    bool isAddCommutative(const Zi& a, const Zi& b);
    bool isAddAssociative(const Zi& a, const Zi& b, const Zi& c);
    bool isAddIdentity(const Zi& a);
    bool isMulCommutative(const Zi& a, const Zi& b);
    bool isMulAssociative(const Zi& a, const Zi& b, const Zi& c);
    bool isMulIdentity(const Zi& a);
    bool isDistributive(const Zi& a, const Zi& b, const Zi& c);
    bool isConjInvolution(const Zi& a);
    bool isConjAdditive(const Zi& a, const Zi& b);
    bool isConjMultiplicative(const Zi& a, const Zi& b);
    bool isNormPositive(const Zi& a);
    bool isNormMultiplicative(const Zi& a, const Zi& b);
    bool verifyBezoutIdentity(const Zi& a, const Zi& b, const XgcdResult& res);
}
Description: Inline property verifiers for algebraic laws
Purpose: Unit testing, property-based testing
Returns: true if property holds for given inputs

Matrix API
cpp
ZiMatrix::ZiMatrix(int32_t a = 0, int32_t b = 0)
Description: Constructs matrix representation of a + bi
Parameters: Real and imaginary components
Postcondition: Matrix encodes the Gaussian integer

cpp
static ZiMatrix ZiMatrix::from_zi(const Zi& z)
Description: Factory method converting Zi to ZiMatrix
Parameters: z - Gaussian integer to encode
Returns: Matrix representation preserving algebraic operations
Isomorphism: 
ϕ
:
Z
[
i
]
→
M
2
(
Z
)
ϕ:Z[i]→M 
2
 (Z) is a ring homomorphism

File Structure
text
math/zi/
├── zi.h              # Core type definitions and API declarations
├── zi.cpp            # Implementation of Zi operations
├── zi_matrix.h       # Matrix representation header
├── zi_matrix.cpp     # Matrix implementation
└── IMPLEMENTATION.md # Algorithm specifications (this file)

tests/
├── zi_test.cpp       # Unit tests for Zi operations
└── zi_matrix_test.cpp # Unit tests for ZiMatrix
Build Integration
Compilation Units
makefile
# Object files
zi.o: math/zi/zi.cpp math/zi/zi.h
    g++ -std=c++17 -O3 -march=native -Wall -Wextra -c $< -o $@

zi_matrix.o: math/zi/zi_matrix.cpp math/zi/zi_matrix.h math/zi/zi.h
    g++ -std=c++17 -O3 -march=native -Wall -Wextra -c $< -o $@
Test Executables
makefile
zi_test: tests/zi_test.cpp zi.o
    g++ -std=c++17 -O3 -march=native -Wall -Wextra $^ -o $@

zi_matrix_test: tests/zi_matrix_test.cpp zi.o zi_matrix.o
    g++ -std=c++17 -O3 -march=native -Wall -Wextra $^ -o $@
Dependencies
External
C++17 standard library (<cstdint>, <cassert>, <iostream>, <random>, <chrono>)

Internal
zi_matrix.h depends on zi.h

Test files depend on corresponding headers

Invariants and Contracts
Class Invariants
Zi:

Components always fit in int32_t

Norm fits in int64_t (guaranteed by component bounds)

DivResult:

N(r) < N(divisor) (Euclidean property)

dividend == divisor * q + r

XgcdResult:

g == gcd(a, b)

g == s*a + t*b

Preconditions
divEuclid: Divisor must be non-zero

All operations: No overflow in int32_t arithmetic for inputs

Postconditions
Division: Remainder norm strictly less than divisor norm

GCD: Result divides both inputs

XGCD: Bézout identity satisfied

Performance Characteristics
Operation	Time	Space	Notes
Constructor	O(1)	O(1)	Trivial initialization
Arithmetic	O(1)	O(1)	Fixed-size operations
Norm	O(1)	O(1)	Two multiplications, one addition
Division	O(1)	O(1)	Constant number of operations
GCD	O(log N)	O(1)	Iterative Euclidean algorithm
XGCD	O(log N)	O(log N)	Stores quotient sequence
Where N = min(norm(a), norm(b))

Usage Examples
Basic Arithmetic
cpp
Zi z1(3, 4);      // 3 + 4i
Zi z2(1, -2);     // 1 - 2i
Zi sum = z1.add(z2);      // 4 + 2i
Zi prod = z1.mul(z2);     // 11 - 2i
int64_t n = z1.norm();    // 25
Division and GCD
cpp
Zi a(13, 11);
Zi b(3, -4);
DivResult div = divEuclid(a, b);
// a = b*div.q + div.r, N(div.r) < N(b)

Zi g = gcd(a, b);
XgcdResult xgcd_res = xgcd(a, b);
// g = xgcd_res.s * a + xgcd_res.t * b
Matrix Operations
cpp
Zi z(3, 4);
ZiMatrix M = ZiMatrix::from_zi(z);
// M = [[3, -4], [4, 3]]
// det(M) = 25 = N(z)
Extension Points
Future Modules
Octavian Integers (math/octavian/):

Similar API structure

8 units instead of 4

Different division algorithm (octagonal tiling)

Hurwitz Integers (math/hurwitz/):

Quaternion structure

24 units

4×4 matrix representation

API Stability
Stable (v1.0):

Core Zi struct layout

All member methods

Free function signatures

DivResult, XgcdResult types

Experimental:

ZiProperties namespace (testing only)

Document: math/zi/API.md
Maintainer: eulerdaddy

