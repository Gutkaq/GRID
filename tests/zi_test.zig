const std = @import("std");
const zi = @import("zi");

// Non-trivial values for conj, norm, isUnit
const q1 = zi.Zi{ .a = 5, .b = 12 };   // 5+12i, norm = 169
const q2 = zi.Zi{ .a = -3, .b = 4 };   // -3+4i, norm = 25
const q3 = zi.Zi{ .a = 0, .b = 1 };    // i, unit
const q4 = zi.Zi{ .a = 1, .b = 1 };    // 1+i, norm = 2

test "conj: involution, additive, multiplicative" {
    try std.testing.expect(zi.Zi.isConjInvolution(q1));
    try std.testing.expect(zi.Zi.isConjAdditive(q1, q2));
    try std.testing.expect(zi.Zi.isConjMultiplicative(q1, q2));
}

test "norm: positive, zero, multiplicative" {
    try std.testing.expect(zi.Zi.isNormPositive(q1));
    try std.testing.expect(zi.Zi.isNormZero(zi.ZERO));
    try std.testing.expect(zi.Zi.isNormMultiplicative(q1, q2));
}

test "isUnit: units {±1, ±i}, non-units false" {
    try std.testing.expect(q3.isUnit()); // i
    try std.testing.expect(zi.ONE.isUnit()); // 1
    try std.testing.expect(zi.ZERO.isUnit() == false); // 0
    try std.testing.expect(q4.isUnit() == false); // 1+i
}

test "explicit: conj(5+12i) = 5-12i" {
    const result = q1.conj();
    const expected = zi.Zi{ .a = 5, .b = -12 };
    try std.testing.expect(result.eq(expected));
}

test "explicit: norm(5+12i) = 169" {
    const result = q1.norm();
    const expected: i64 = 169;
    try std.testing.expect(result == expected);
}
