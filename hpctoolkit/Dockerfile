FROM debian:11

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get -y install python3 gcc cmake g++ libopenmpi-dev git xz-utils bzip2

RUN git clone https://github.com/spack/spack && \
    . ./spack/share/spack/setup-env.sh && \
    mkdir /hpctoolkit-env && \
    spack env activate /hpctoolkit-env && \
    spack install hpctoolkit
