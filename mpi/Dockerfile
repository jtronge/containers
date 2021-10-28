FROM debian:11

RUN apt-get update && \
    apt-get install openmpi-bin pmix gcc

COPY mpi.c /
RUN mpicc -o mpi mpi.c
