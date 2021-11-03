FROM debian:11


ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update && \
    apt-get -y install git cmake gcc g++ gfortran libopenmpi-dev openmpi-bin \
                       libpmix-dev libpmix-bin libhdf5-dev libnetcdf-dev wget \
                       libboost-all-dev libexodusii-dev curl libmetis-dev \
                       libluajit-5.1-dev

# Install exodus
#RUN git clone https://github.com/gsjaardema/seacas.git && \
#    cd seacas && \
#    ./install-tpl.sh && \
#    mkdir build && \
#    cd build && \
#    ../cmake-exodus && \
#    make && \
#    make install

# Install BOOST (we need everything)
# RUN apt-get -y install libparmetis-dev
# RUN apt-get -y install libscotchparmetis-dev
# RUN apt-get -y install libptscotch-dev

# Install ParMetis manually
RUN curl -O -L http://glaros.dtc.umn.edu/gkhome/fetch/sw/parmetis/parmetis-4.0.3.tar.gz && \
    tar -xvf parmetis-4.0.3.tar.gz && \
    cd parmetis-4.0.3 && \
    make config prefix=/usr && \
    make && \
    make install

# For some reason the ristra package needs lua5.2
RUN apt-get -y install lua5.2
RUN apt-get -y install lua5.2-dev

# Install flecsale
RUN git clone -b stable --recursive https://github.com/laristra/flecsale.git && \
    cd flecsale && \
    mkdir build && \
    cd build && \
    CC=mpicc CXX=mpic++ cmake ../ -DENABLE_COLORING=on -DENABLE_LUA=ON && \
    make -j8
    # CC=mpicc CXX=mpic++ cmake ../ -DFLECSI_RUNTIME_MODEL="mpi" -DENABLE_COLORING=on && \
