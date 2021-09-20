FROM debian:10

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update && \
    apt-get -y install git cmake gcc g++ gfortran libmagickcore-dev libmagickwand-dev

RUN git clone https://github.com/lanl/CLAMR.git
RUN cd CLAMR && cmake . && make
