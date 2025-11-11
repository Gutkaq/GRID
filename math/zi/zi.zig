const std = @import("std");

pub const Zi = struct {
    a: i32,
    b: i32,
    
    //Equality checks
    pub fn eq(self: Zi, other: Zi) bool {
        return self.a == other.a and self.b == other.b;
    }
    
    // Standard Zi addition
    pub fn add(self: Zi, other: Zi) Zi {
        return .{ .a = self.a + other.a, .b = self.b + other.b };
    }

    pub fn sub(self: Zi, other: Zi) Zi {
        return .{ .a = self.a - other.a, .b = self.b - other.b };
    }
    
    //Standard Zi multiplication with overflow safe
    pub fn mul(self: Zi, other: Zi) Zi {
        const ac: i64 = @as(i64, self.a) * @as(i64, other.a);
        const bd: i64 = @as(i64, self.b) * @as(i64, other.b);
        const ad: i64 = @as(i64, self.a) * @as(i64, other.b);
        const bc: i64 = @as(i64, self.b) * @as(i64, other.a);
        return .{ .a = @intCast(ac - bd), .b = @intCast(ad + bc) };
    }
    
    //Conjugation
    pub fn conj(self: Zi) Zi {
        return .{ .a = self.a, .b = -self.b };
    }

    //Norm
    pub fn norm(self: Zi) i64 {
        const a2: i64 = @as(i64, self.a) * self.a;
        const b2: i64 = @as(i64, self.b) * self.b;
        return a2 + b2;
    }

    // Property checks in impl
    
    // isUnit: norm == 1
    pub fn isUnit(self: Zi) bool {
        return self.norm() == 1;
    }

    // for conj and Norm
    pub fn isConjInvolution(a: Zi) bool {
        return a.conj().conj().eq(a);
    }

    pub fn isConjAdditive(a: Zi, b: Zi) bool {
        return a.add(b).conj().eq(a.conj().add(b.conj()));
    }

    pub fn isConjMultiplicative(a: Zi, b: Zi) bool {
        return a.mul(b).conj().eq(a.conj().mul(b.conj()));
    }

    pub fn isNormPositive(a: Zi) bool {
        return a.norm() >= 0;
    }

    pub fn isNormZero(a: Zi) bool {
        return a.norm() == 0 and a.eq(ZERO);
    }

    pub fn isNormMultiplicative(a: Zi, b: Zi) bool {
        return a.mul(b).norm() == a.norm() * b.norm();
    }

    pub fn isAddCommutative(a: Zi, b: Zi) bool {
        return a.add(b).eq(b.add(a));
    }

    pub fn isAddAssociative(a: Zi, b: Zi, c: Zi) bool {
        return a.add(b.add(c)).eq(a.add(b).add(c));
    }

    pub fn isAddIdentity(a: Zi) bool {
        return a.add(ZERO).eq(a);
    }

    pub fn isMulCommutative(a: Zi, b: Zi) bool {
        return a.mul(b).eq(b.mul(a));
    }

    pub fn isMulAssociative(a: Zi, b: Zi, c: Zi) bool {
        return a.mul(b.mul(c)).eq(a.mul(b).mul(c));
    }

    pub fn isMulIdentity(a: Zi) bool {
        return a.mul(ONE).eq(a);
    }

    pub fn isDistributiveLeft(a: Zi, b: Zi, c: Zi) bool {
        return a.mul(b.add(c)).eq(a.mul(b).add(a.mul(c)));
    }

    pub fn isDistributiveRight(a: Zi, b: Zi, c: Zi) bool {
        return a.add(b).mul(c).eq(a.mul(c).add(b.mul(c)));
    }
};

pub const ZERO = Zi{ .a = 0, .b = 0 };
pub const ONE = Zi{ .a = 1, .b = 0 };
pub const I = Zi{ .a = 0, .b = 1 };
