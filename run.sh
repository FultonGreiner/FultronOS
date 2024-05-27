#!/usr/bin/env bash

readonly KERNEL=$1

readonly KERNEL_PREFIX_PATH=target/aarch64-fultronos/
readonly KERNEL_BINARY=/fultronos

readonly TARGET_STRIPPED=${KERNEL#*$KERNEL_PREFIX_PATH}
readonly TARGET_PROFILE=${TARGET_STRIPPED%$KERNEL_BINARY*}

QEMU_FLAGS_LIST=(
    -machine virt,virtualization=on,gic-version=3
    -cpu cortex-a53
    -nographic
    -smp 1
    -m 2048
    -kernel $KERNEL
    -serial mon:stdio
    -monitor none
    -no-reboot
)

if [ "$TARGET_PROFILE" == "release" ]; then
    echo "Running release binary ..."
else
    echo "Running debug binary ..."
    QEMU_FLAGS_LIST+=(-S -s)
fi

QEMU_FLAGS=$(IFS=' '; echo "${QEMU_FLAGS_LIST[*]}")

qemu-system-aarch64 $QEMU_FLAGS
