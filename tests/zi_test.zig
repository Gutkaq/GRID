const std = @import("std");
const zi = @import("zi");  // Thsis is the module we wrote see the build file1

test "eq: identity and distinction" {
    try std.testing.expect(zi.ONE.eq(zi.ONE));
    try std.testing.expect(zi.I.eq(zi.I));
    try std.testing.expect(zi.ZERO.eq(zi.ZERO));

    try std.testing.expect(!zi.ONE.eq(zi.I));
    try std.testing.expect(!zi.ONE.eq(zi.ZERO));
    try std.testing.expect(!zi.I.eq(zi.ZERO));
}
