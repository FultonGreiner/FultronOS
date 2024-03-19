FROM ubuntu:22.04 as i386-elf-builder

RUN apt update
RUN apt upgrade -y
RUN apt install -y --no-install-recommends --quiet \
    bison \
    build-essential \
    curl \
    flex \
    git \
    libgmp3-dev \
    libmpc-dev \
    libmpfr-dev \
    texinfo \
    wget
RUN apt clean

RUN export PREFIX=/root/opt/cross
RUN export TARGET=i386-elf
RUN export PATH="$PREFIX/bin:$PATH"

WORKDIR /_work/src
RUN wget --no-check-certificate https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
RUN tar -xf binutils-2.42.tar.xz

WORKDIR /_work/src/binutils-2.42
RUN ./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
RUN make
RUN make install

WORKDIR /_work/src
RUN wget --no-check-certificate https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz
RUN tar -xf gcc-13.2.0.tar.gz

WORKDIR /_work/src/gcc-13.2.0
RUN ./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
RUN make all-gcc
RUN make all-target-libgcc
RUN make install-gcc
RUN make install-target-libgcc

FROM i386-elf-builder as i386-elf-runner

COPY --from=i386-elf-builder /root/opt /root/opt
RUN /root/opt/cross/bin/$TARGET-gcc --version
