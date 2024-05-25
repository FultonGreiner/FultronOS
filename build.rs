use std::env;
use std::process::Command;

/// Build script to set environment variables for the git branch, commit hash,
/// and package version, as well as to compile assembly files and specify linker arguments.
fn main() {
    // Get the current git branch
    let branch = Command::new("git")
        .args(&["rev-parse", "--abbrev-ref", "HEAD"])
        .output()
        .expect("Failed to get git branch")
        .stdout;
    let branch = String::from_utf8(branch)
        .expect("Invalid UTF-8 in git branch")
        .trim()
        .to_string();

    // Get the current git commit hash
    let commit = Command::new("git")
        .args(&["rev-parse", "HEAD"])
        .output()
        .expect("Failed to get git commit hash")
        .stdout;
    let commit = String::from_utf8(commit)
        .expect("Invalid UTF-8 in git commit hash")
        .trim()
        .to_string();

    // Get the current package version from environment variables
    let cargo_pkg_version = env!("CARGO_PKG_VERSION");

    // Set environment variables for branch, commit, and package version
    println!("cargo:rustc-env=GIT_BRANCH={}", branch);
    println!("cargo:rustc-env=GIT_COMMIT={}", commit);
    println!("cargo:rustc-env=CARGO_PKG_VERSION={}", cargo_pkg_version);

    // // Add linker arguments
    println!("cargo:rustc-link-arg=-nostartfiles");
    println!("cargo:rustc-link-arg=-nostdlib");
    println!("cargo:rustc-link-arg=-Tarch/aarch64/src/linker.ld");
}
