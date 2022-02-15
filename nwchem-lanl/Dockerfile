# thanks to heasterday for putting this together
FROM quay.io/centos/centos:stream8
RUN dnf install -y epel-release \
 && dnf install -y --setopt=skip_missing_names_on_install=0 \
                autoconf \
                automake \
                file \
                flex \
                gcc \
                gcc-c++ \
                gcc-gfortran \
                git \
                make \
                python3-devel \
                python3 \
                wget \
                ibacm \
                libevent-devel \
                libtool \
                libibumad \
                libibumad-devel \
                libibverbs \
                libibverbs-devel \
                libibverbs-utils \
                librdmacm \
                librdmacm-devel \
                rdma-core \
                make \
                numactl-devel \
                which \
                unzip \
                tzdata \
                patch \
                tcsh \
                openssh-clients \
                openssl-devel \
                bzip2 \
 && dnf install -y --setopt=install_weak_deps=false --skip-broken \
                libpsm2 \
                libpsm2-devel \
 && dnf clean all

RUN echo "/usr/local/lib" > /etc/ld.so.conf.d/usrlocal.conf \
 && echo "/usr/local/lib64" >> /etc/ld.so.conf.d/usrlocal.conf \
 && ldconfig

ARG NUMJOBS=2

# PMI2 installation below is copied from the Charliecloud example Dockerfile
#
# PMI2.
#
# CentOS doesn't have a package with the Slurm PMI2 libraries we need, so
# build them from Slurm's release.
ARG SLURM_VERSION=21.08.5
RUN wget https://download.schedmd.com/slurm/slurm-${SLURM_VERSION}.tar.bz2 \
 && tar -xf slurm-${SLURM_VERSION}.tar.bz2 \
 && cd slurm-${SLURM_VERSION} \
 && ./configure --prefix=/usr/local \
 && cd contribs/pmi2 \
 && make -j$NUMJOBS install \
 && rm -Rf ../../../slurm*

ARG MPI_URL=https://www.open-mpi.org/software/ompi/v4.1/downloads
ARG MPI_VERSION=4.1.2
RUN wget -nv ${MPI_URL}/openmpi-${MPI_VERSION}.tar.gz \
 && tar xf openmpi-${MPI_VERSION}.tar.gz \
 && cd openmpi-${MPI_VERSION} \
 && CFLAGS=-O3 \
    CXXFLAGS=-O3 \
    ./configure --prefix=/usr/local \
                --sysconfdir=/mnt/0 \
                --with-slurm \
                --with-pmi=/usr/local \
                --with-pmix \
                --with-ompi-pmix-rte \
                --disable-pty-support \
                --enable-mca-no-build=btl-openib,plm-slurm \
                --enable-mpi1-compatibility \
 && make -j$NUMJOBS install \
 && rm -Rf ../openmpi-${MPI_VERSION}*
RUN ldconfig
RUN echo 'plm_rsh_agent = false' >> /mnt/0/openmpi-mca-params.conf

ARG VERSION=master
ENV ARMCI_NETWORK=MPI-PR
ENV NWCHEM_TARGET=LINUX64
ENV NWCHEM_MODULES="all python"
ENV USE_INTERNALBLAS=y
ENV BUILD_SCALAPACK=1
ENV BLAS_SIZE=8
ENV SCALAPACK_SIZE=8
ENV USE_MPI=y
ENV USE_MPIF=y
ENV USE_MPIF4=y
ENV USE_HWOPT=n
ENV USE_LIBXC=y
ENV USE_NOIO=y
ENV USE_SIMINT=y
ENV SIMINT_MAXAM=5
ENV NWCHEM_TOP=/nwchem

ARG CMAKE_VERSION=3.22.0
RUN wget https://cmake.org/files/v3.22/cmake-${CMAKE_VERSION}.tar.gz \
 && tar xf cmake-${CMAKE_VERSION}.tar.gz \
 && cd cmake-${CMAKE_VERSION} \
 && ./bootstrap --prefix=/usr \
 && make -j$NUMJOBS \
 && make -j$NUMJOBS install \
 && rm -Rf ../cmake-${CMAKE_VERSION}*

RUN curl -L https://api.github.com/repos/nwchemgit/nwchem/tarball/$VERSION > nwchem.tar.gz \
 && mkdir -p nwchem \
 && cd nwchem \
 && tar zxf ../nwchem.tar.gz --strip-components=1 \
 && cd src \
 && make -j$NUMJOBS nwchem_config \
 && make -j$NUMJOBS \
 && make -j$NUMJOBS install INSTALL_PREFIX=/opt/nwchem
