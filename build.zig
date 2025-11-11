const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // === TEST: zi_test.zig ===
    const zi_test = b.addTest(.{
        .root_source_file = b.path("tests/zi_test.zig"),
        .target = target,
        .optimize = optimize,
    });

    // Add math/zi as module
    const zi_module = b.createModule(.{
        .root_source_file = b.path("math/zi/zi.zig"),
    });
    zi_test.root_module.addImport("zi", zi_module);

    // === RUN TEST WITH VERBOSE OUTPUT ===
    const run_zi_test = b.addRunArtifact(zi_test);
    run_zi_test.has_side_effects = true;  // This forces output

    // === TEST STEP ===
    const test_step = b.step("test", "Run all tests");
    test_step.dependOn(&run_zi_test.step);

    // === DEFAULT: zig build = test ===
    b.default_step = test_step;
}
