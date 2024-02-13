const std = @import("std");

const c_src = &.{
    "main.c",
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});

    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "vector",
        .target = target,
        .optimize = optimize,
    });
    inline for (c_src) |src_file| {
        exe.addCSourceFile(.{
            .file = .{ .path = "src/" ++ src_file },
            .flags = &.{},
        });
    }
    exe.linkLibC();

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);

    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
