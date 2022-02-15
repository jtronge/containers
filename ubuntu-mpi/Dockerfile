# Modified MPI base container for use with Charliecloud.
#
# Based on
# https://github.com/edoapra/nwchem-singularity/tree/master/nwchem-dev.ompi40x
#Bootstrap: docker
FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update && \
    apt-get -y install -y tzdata git && \
    apt-get -y install -y curl wget tar libnl-3-200 libnl-route-3-200 libgomp1 libnuma1 \
       g++ gfortran   make ssh patch curl  wget unzip perl-base file \
       python3 python3-dev cmake  unzip zip perl automake libtool autoconf flex  \
       libnuma-dev libslurm-dev libnl-3-dev libnl-route-3-dev udev libevent-dev \
       hwloc libhwloc-dev libpmi2-0
ARG NUMJOBS=8
ENV PMIX_DIR=/opt/pmix
# Install PMIx
RUN curl -O -L https://github.com/openpmix/openpmix/releases/download/v4.1.0/pmix-4.1.0.tar.bz2 && \
    tar -xvf pmix-4.1.0.tar.bz2 && \
    cd pmix-4.1.0 && \
    ./configure --prefix=/opt/pmix --disable-man-pages && \
    make -j$NUMJOBS && \
    make install && \
    echo "$PMIX_DIR/lib" >> /etc/ld.so.conf.d/pmix.conf && \
    ldconfig
# Install PMI2 manually (based on Charliecloud example)
ENV PMI_DIR=/opt/pmi
ARG SLURM_VERSION=21.08.5
RUN curl -O -L https://download.schedmd.com/slurm/slurm-$SLURM_VERSION.tar.bz2 && \
    tar -xvf slurm-$SLURM_VERSION.tar.bz2 && \
    cd slurm-$SLURM_VERSION && \
    ./configure --prefix=$PMI_DIR && \
    cd contribs/pmi2 && \
    make install
# Install OpenMPI
ENV OMPI_DIR=/opt/mpi
RUN curl -O -L https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.2.tar.bz2 && \
    tar -xvf openmpi-4.1.2.tar.bz2 && \
    cd openmpi-4.1.2 && \
    ./configure --prefix=$OMPI_DIR --with-pmix=$PMIX_DIR --with-pmi=$PMI_DIR \
                --with-ompi-pmix-rte --with-slurm --enable-mpi1-compatibility && \
    make -j$NUMJOBS && \
    make install && \
    echo "$OMPI_DIR/lib" >> /etc/ld.so.conf.d/mpi.conf && \
    ldconfig
