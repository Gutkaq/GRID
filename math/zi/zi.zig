const std = @import("std");

pub const Zi = struct {
    a: i32,
    b: i32,

    pub fn eq(self: Zi, other: Zi) bool {
        return self.a == other.a and self.b == other.b;
    }
};

// Core constants
pub const ZERO = Zi{ .a = 0, .b = 0 };
pub const ONE = Zi{ .a = 1, .b = 0};
pub const I = Zi{ .a = 0, .b = 1};
