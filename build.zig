const std = @import("std");

const c_lib_src = &.{
    "vector.c",
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});

    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "vector",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFile(.{
        .file = .{ .path = "src/main.c" },
        .flags = &.{},
    });

    const lib = b.addStaticLibrary(.{
        .name = "vector",
        .target = target,
        .optimize = optimize,
    });
    inline for (c_lib_src) |src_file| {
        lib.addCSourceFile(.{
            .file = .{ .path = "src/" ++ src_file },
            .flags = &.{},
        });
    }
    lib.linkLibC();

    b.installArtifact(lib);

    exe.linkLibrary(lib);

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
