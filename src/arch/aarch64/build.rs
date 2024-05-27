extern crate cc;

fn main() {
    // Instruct Cargo to rerun this build script if certain files change
    println!("cargo:rerun-if-changed=src/arch/start.s");
    println!("cargo:rerun-if-changed=src/linker.ld");

    // Compile the assembly file
    cc::Build::new()
        .file("src/start.s")
        .file("src/vector.s")
        .flag("-mcpu=cortex-a53")
        .compile("start");

    // Add linker arguments
    println!("cargo:rustc-link-arg=-nostartfiles");
    println!("cargo:rustc-link-arg=-nostdlib");
}
