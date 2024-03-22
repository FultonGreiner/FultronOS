import os, shutil, sys
from invoke import Collection, Config, Exit, task
from shutil import which

from typing import Final

BAZEL_EXE: Final[str] = "bazel"

@task
def build(ctx):
    """Build the kernel image"""
    cmd = f"{BAZEL_EXE} build --config=arm //source:fultronos.elf"
    ctx.run(cmd)

@task
def clean(ctx):
    """Clean the build directory"""
    cmd = f"{BAZEL_EXE} clean --async"
    ctx.run(cmd)

# Add tasks to the namespace
fultronos = Collection(build, clean)
config = Config(defaults={"run": {"pty": True}})
fultronos.configure(config)