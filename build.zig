const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});

    const zi_test = b.addTest(.{
        .root_source_file = b.path("tests/zi_test.zig"),
        .target = target,
        .optimize = .ReleaseFast,  // Direct, no unused const
    });

    zi_test.root_module.addImport("zi", b.createModule(.{
        .root_source_file = b.path("math/zi/zi.zig"),
    }));

    const run_test = b.addRunArtifact(zi_test);

    const test_step = b.step("test", "Run Zi tests + benchmark");
    test_step.dependOn(&run_test.step);

    b.default_step = test_step;
}
