import os, shutil, sys
from invoke import Collection, Config, Exit, task
from shutil import which

from typing import Final

BAZEL_EXE: Final[str] = "bazel"
RENODE_EXE: Final[str] = "/Applications/Renode.app/Contents/MacOS/macos_run.command"

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

@task
def emulate(ctx):
    """Launch the kernel image in renode"""
    cmd = f"{RENODE_EXE} tools/renode/renode-config.resc"
    ctx.run(cmd)

# Add tasks to the namespace
fultronos = Collection(build, clean)
config = Config(defaults={"run": {"pty": True}})
fultronos.configure(config)