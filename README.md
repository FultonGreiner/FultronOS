# FultronOS

FultronOS is meant to provide a lightweight, yet powerful operating system for networking devices. I started this project to combine my goals of learning advanced Networking, OS Theory, and Rust.

## Directory Structure

```bash
.
├── arch              # Architecture specific modules
│   └── aarch64       # AArch64 specific modules
├── build.rs          # Build configuration
├── common            # Shared modules
├── devices           # Device-related modules
├── drivers           # Device drivers
└── src               # Primary kernel source
```

## Getting Started

### Prerequisites

* QEMU for ARM64 emulation
* Rust and Cargo

### Installation Commands

```bash
# update package repositories
sudo apt update

# Install QEMU
sudo apt install -y qemu-system-arm

# Install Rust and Cargo
curl https://sh.rustup.rs -sSf | sh

# Install Rust nightly release
rustup install nightly

# Default to Rust nightly release
rustup default nightly
```

## Building the Project

```bash
cargo build
```

## Running FultronOS

```bash
cargo run
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License.
