#!/bin/bash
rm sum.o
./as11 -l sum.l -o sum.o $1
cp sum.o ../cmake-build-debug/sum.o
