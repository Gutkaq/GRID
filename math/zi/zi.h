#ifndef ZI_H
#define ZI_H

#include <cstdint>
#include <cassert>

struct Zi {
    int32_t a, b;

    Zi();
    Zi(int32_t real, int32_t imag);

    bool eq(const Zi& other) const;
    Zi add(const Zi& other) const;
    Zi sub(const Zi& other) const;
    Zi mul(const Zi& other) const;
    Zi conj() const;
    int64_t norm() const;
    bool isUnit() const;
    bool isZero() const;
    bool isAssociate(const Zi& other) const;
};

struct DivResult {
    Zi q, r;
};

struct XgcdResult {
    Zi g, s, t;
};

extern const Zi ZERO;
extern const Zi ONE;
extern const Zi I;

DivResult divEuclid(const Zi& self, const Zi& other);
Zi gcd(const Zi& self, const Zi& other);
XgcdResult xgcd(const Zi& self, const Zi& other);

namespace ZiProperties {
    inline bool isAddCommutative(const Zi& a, const Zi& b) {
        return a.add(b).eq(b.add(a));
    }

    inline bool isAddAssociative(const Zi& a, const Zi& b, const Zi& c) {
        return a.add(b.add(c)).eq(a.add(b).add(c));
    }

    inline bool isAddIdentity(const Zi& a) {
        return a.add(ZERO).eq(a);
    }

    inline bool isMulCommutative(const Zi& a, const Zi& b) {
        return a.mul(b).eq(b.mul(a));
    }

    inline bool isMulAssociative(const Zi& a, const Zi& b, const Zi& c) {
        return a.mul(b.mul(c)).eq(a.mul(b).mul(c));
    }

    inline bool isMulIdentity(const Zi& a) {
        return a.mul(ONE).eq(a);
    }

    inline bool isDistributiveLeft(const Zi& a, const Zi& b, const Zi& c) {
        return a.mul(b.add(c)).eq(a.mul(b).add(a.mul(c)));
    }

    inline bool isDistributiveRight(const Zi& a, const Zi& b, const Zi& c) {
        return a.add(b).mul(c).eq(a.mul(c).add(b.mul(c)));
    }

    inline bool isConjInvolution(const Zi& a) {
        return a.conj().conj().eq(a);
    }

    inline bool isConjAdditive(const Zi& a, const Zi& b) {
        return a.add(b).conj().eq(a.conj().add(b.conj()));
    }

    inline bool isConjMultiplicative(const Zi& a, const Zi& b) {
        return a.mul(b).conj().eq(a.conj().mul(b.conj()));
    }

    inline bool isNormPositive(const Zi& a) {
        return a.norm() >= 0;
    }

    inline bool isNormZero(const Zi& a) {
        return a.norm() == 0 && a.eq(ZERO);
    }

    inline bool isNormMultiplicative(const Zi& a, const Zi& b) {
        return a.mul(b).norm() == a.norm() * b.norm();
    }

    inline bool isGcdUnit(const Zi& a, const Zi& b) {
        Zi g = gcd(a, b);
        return g.isUnit();
    }

    inline bool isBezoutIdentity(const Zi& a, const Zi& b) {
        XgcdResult res = xgcd(a, b);
        return res.g.eq(res.s.mul(a).add(res.t.mul(b)));
    }
}

#endif // ZI_H
