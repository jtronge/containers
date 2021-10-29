FROM debian:11

RUN apt-get update && \
    apt-get install -y libopenmpi-dev openmpi-bin libpmix-dev libpmix-bin

COPY mpi.c /
RUN mpicc -o mpi mpi.c
