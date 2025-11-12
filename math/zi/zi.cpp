#include "zi.h"
#include <cmath>

Zi::Zi() : a(0), b(0) {}
Zi::Zi(int32_t real, int32_t imag) : a(real), b(imag) {}

bool Zi::eq(const Zi& other) const {
    return a == other.a && b == other.b;
}

Zi Zi::add(const Zi& other) const {
    return Zi(a + other.a, b + other.b);
}

Zi Zi::sub(const Zi& other) const {
    return Zi(a - other.a, b - other.b);
}

Zi Zi::mul(const Zi& other) const {
    int64_t ac = static_cast<int64_t>(a) * other.a;
    int64_t bd = static_cast<int64_t>(b) * other.b;
    int64_t ad = static_cast<int64_t>(a) * other.b;
    int64_t bc = static_cast<int64_t>(b) * other.a;
    return Zi(static_cast<int32_t>(ac - bd), static_cast<int32_t>(ad + bc));
}

Zi Zi::conj() const {
    return Zi(a, -b);
}

int64_t Zi::norm() const {
    int64_t a2 = static_cast<int64_t>(a) * a;
    int64_t b2 = static_cast<int64_t>(b) * b;
    return a2 + b2;
}

bool Zi::isUnit() const {
    return norm() == 1;
}

bool Zi::isZero() const {
    return eq(ZERO);
}

bool Zi::isAssociate(const Zi& other) const {
    if (other.isZero()) return isZero();
    Zi units[4] = {ONE, I, Zi(-1, 0), Zi(0, -1)};
    for (int i = 0; i < 4; ++i) {
        if (eq(other.mul(units[i]))) return true;
    }
    return false;
}

static int32_t gaussian_round(double x) {
    return static_cast<int32_t>(std::round(x));
}

DivResult divEuclid(const Zi& self, const Zi& other) {
    assert(!other.isZero());

    Zi conj_b = other.conj();
    Zi num = self.mul(conj_b);
    double den = static_cast<double>(other.norm());

    double q_a_real = static_cast<double>(num.a) / den;
    double q_b_real = static_cast<double>(num.b) / den;

    int32_t q_a = gaussian_round(q_a_real);
    int32_t q_b = gaussian_round(q_b_real);
    Zi q = Zi(q_a, q_b);

    Zi r = self.sub(other.mul(q));
    assert(r.norm() <= other.norm());
    return DivResult{q, r};
}

Zi gcd(const Zi& self, const Zi& other) {
    Zi a = self;
    Zi b = other;
    while (!b.isZero()) {
        DivResult div = divEuclid(a, b);
        a = b;
        b = div.r;
    }
    return a;
}

XgcdResult xgcd(const Zi& self, const Zi& other) {
    Zi old_r = self;
    Zi r = other;
    Zi old_s = ONE;
    Zi s = ZERO;
    Zi old_t = ZERO;
    Zi t = ONE;

    while (!r.isZero()) {
        DivResult div = divEuclid(old_r, r);
        Zi q = div.q;

        Zi new_r = old_r.sub(q.mul(r));
        old_r = r;
        r = new_r;

        Zi new_s = old_s.sub(q.mul(s));
        old_s = s;
        s = new_s;

        Zi new_t = old_t.sub(q.mul(t));
        old_t = t;
        t = new_t;
    }

    return XgcdResult{old_r, old_s, old_t};
}

const Zi ZERO = Zi(0, 0);
const Zi ONE = Zi(1, 0);
const Zi I = Zi(0, 1);
