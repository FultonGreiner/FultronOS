ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

LIBCDIR = $(ROOT_DIR)/libc

all: libc

.PHONY: libc
libc:
	$(MAKE) -C $(LIBCDIR) all
