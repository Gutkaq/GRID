const std = @import("std");
const zi = @import("zi");

var prng = std.rand.DefaultPrng.init(0x12345678);
const rand = prng.random();

fn randomZi() zi.Zi {
    return zi.Zi{
        .a = rand.intRangeAtMost(i32, -100000, 100000),
        .b = rand.intRangeAtMost(i32, -100000, 100000),
    };
}

test "ring laws: 1000 random values" {
    const trials = 1000;
    var i: usize = 0;
    while (i < trials) : (i += 1) {
        const a = randomZi();
        const b = randomZi();
        const c = randomZi();

        try std.testing.expect(zi.Zi.isAddCommutative(a, b));
        try std.testing.expect(zi.Zi.isAddAssociative(a, b, c));
        try std.testing.expect(zi.Zi.isAddIdentity(a));

        try std.testing.expect(zi.Zi.isMulCommutative(a, b));
        try std.testing.expect(zi.Zi.isMulAssociative(a, b, c));
        try std.testing.expect(zi.Zi.isMulIdentity(a));

        try std.testing.expect(zi.Zi.isDistributiveLeft(a, b, c));
        try std.testing.expect(zi.Zi.isDistributiveRight(a, b, c));
    }
}

test "benchmark: mul 1_000_000 times" {
    var i: usize = 0;
    const iters = 1_000_000;
    var sum = zi.ZERO;

    var timer = try std.time.Timer.start();
    while (i < iters) : (i += 1) {
        const a = randomZi();
        const b = randomZi();
        sum = sum.add(a.mul(b));
    }
    const elapsed = timer.read();

    const ns_per_op = @as(f64, @floatFromInt(elapsed)) / @as(f64, @floatFromInt(iters));
    std.debug.print("\n1M mul ops: {d:.2} ns/op\n", .{ns_per_op});

    try std.testing.expect(sum.a != 0 or sum.b != 0);
}
