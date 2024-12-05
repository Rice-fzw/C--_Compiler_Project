FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    cmake \
    bison \
    clang \
    lld \
    qemu-user-static

WORKDIR /workspace