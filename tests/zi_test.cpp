#include "../math/zi/zi.h"
#include <cassert>
#include <iostream>
#include <random>
#include <chrono>

std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int32_t> dist(-1000, 1000);

Zi random_zi() {
    return Zi(dist(rng), dist(rng));
}

void print_zi(const Zi& z, const std::string& name) {
    std::cout << name << " = " << z.a;
    if (z.b >= 0) std::cout << "+";
    std::cout << z.b << "i";
    std::cout << " | norm = " << z.norm() << "\n";
}

void test_divEuclid() {
    Zi a = Zi(13, 11);
    Zi b = Zi(3, -4);

    std::cout << "\n--- Euclidean Division Test ---\n";
    print_zi(a, "a");
    print_zi(b, "b");

    DivResult res = divEuclid(a, b);
    print_zi(res.q, "q");
    print_zi(res.r, "r");

    Zi recomposed = b.mul(res.q).add(res.r);
    print_zi(recomposed, "b*q + r");

    assert(a.eq(recomposed));
    assert(res.r.norm() <= b.norm());
    std::cout << "PASS: a = b*q + r, norm(r) <= norm(b)\n";
}

void test_gcd() {
    Zi a = Zi(13, 11);
    Zi b = Zi(3, -4);
    Zi g = gcd(a, b);
    Zi expected = Zi(1, 2);

    std::cout << "\n--- GCD Test ---\n";
    print_zi(a, "a");
    print_zi(b, "b");
    print_zi(g, "gcd(a,b)");
    print_zi(expected, "expected (up to unit)");

    assert(g.isAssociate(expected));
    std::cout << "PASS: gcd correct (up to unit)\n";
}

void test_xgcd() {
    Zi a = Zi(13, 11);
    Zi b = Zi(3, -4);
    XgcdResult res = xgcd(a, b);
    Zi computed = res.s.mul(a).add(res.t.mul(b));

    std::cout << "\n--- XGCD (Bézout) Test ---\n";
    print_zi(a, "a");
    print_zi(b, "b");
    print_zi(res.g, "g");
    print_zi(res.s, "s");
    print_zi(res.t, "t");
    print_zi(computed, "s*a + t*b");

    assert(res.g.isAssociate(computed));
    std::cout << "PASS: Bézout identity holds\n";
}

void fuzz_ring_laws(int trials = 1000) {
    std::cout << "\n--- Fuzz Ring Laws (" << trials << " trials) ---\n";
    for (int i = 0; i < trials; ++i) {
        Zi x = random_zi();
        Zi y = random_zi();
        Zi z = random_zi();

        assert(ZiProperties::isAddCommutative(x, y));
        assert(ZiProperties::isAddAssociative(x, y, z));
        assert(ZiProperties::isAddIdentity(x));

        assert(ZiProperties::isMulCommutative(x, y));
        assert(ZiProperties::isMulAssociative(x, y, z));
        assert(ZiProperties::isMulIdentity(x));

        assert(ZiProperties::isDistributiveLeft(x, y, z));
        assert(ZiProperties::isDistributiveRight(x, y, z));
    }
    std::cout << "PASS: All ring laws hold under fuzz\n";
}

void fuzz_conj_norm(int trials = 1000) {
    std::cout << "\n--- Fuzz Conj & Norm (" << trials << " trials) ---\n";
    for (int i = 0; i < trials; ++i) {
        Zi x = random_zi();
        Zi y = random_zi();

        assert(ZiProperties::isConjInvolution(x));
        assert(ZiProperties::isConjAdditive(x, y));
        assert(ZiProperties::isConjMultiplicative(x, y));

        assert(ZiProperties::isNormPositive(x));
        assert(ZiProperties::isNormZero(ZERO));
        assert(ZiProperties::isNormMultiplicative(x, y));
    }
    std::cout << "PASS: Conj & norm laws hold\n";
}

void benchmark_ops(int ops = 1'000'000) {
    std::cout << "\n--- Benchmark: " << ops << " ops each ---\n";
    Zi sum_add = ZERO;
    Zi sum_sub = ZERO;
    Zi sum_mul = ZERO;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < ops; ++i) {
        Zi x = random_zi();
        Zi y = random_zi();
        sum_add = sum_add.add(x.add(y));
        sum_sub = sum_sub.add(x.sub(y));
        sum_mul = sum_mul.add(x.mul(y));
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    double ns_per_add = static_cast<double>(ns) / (3 * ops);
    double ns_per_sub = ns_per_add;
    double ns_per_mul = ns_per_add;

    std::cout << "Total time (add+sub+mul): " << ns << " ns\n";
    std::cout << "Per add: ~" << ns_per_add << " ns/op\n";
    std::cout << "Per sub: ~" << ns_per_sub << " ns/op\n";
    std::cout << "Per mul: ~" << ns_per_mul << " ns/op\n";

    std::cout << "sum_add.norm() = " << sum_add.norm() << "\n";
    std::cout << "sum_sub.norm() = " << sum_sub.norm() << "\n";
    std::cout << "sum_mul.norm() = " << sum_mul.norm() << "\n";

    assert(sum_add.norm() != 0);
    assert(sum_sub.norm() != 0);
    assert(sum_mul.norm() != 0);
}

int main() {
    test_divEuclid();
    test_gcd();
    test_xgcd();
    fuzz_ring_laws();
    fuzz_conj_norm();
    benchmark_ops();

    std::cout << "\nALL TESTS PASSED. LATTICE RISES.\n";
    return 0;
}
