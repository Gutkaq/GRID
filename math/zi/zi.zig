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
    
    //Standard Zi multiplication with overflow safe
    pub fn mul(self: Zi, other: Zi) Zi {
        const ac: i64 = @as(i64, self.a) * @as(i64, other.a);
        const bd: i64 = @as(i64, self.b) * @as(i64, other.b);
        const ad: i64 = @as(i64, self.a) * @as(i64, other.b);
        const bc: i64 = @as(i64, self.b) * @as(i64, other.a);
        return .{ .a = @intCast(ac - bd), .b = @intCast(ad + bc) };
    }

    // Property checks in impl
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
