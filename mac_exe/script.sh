#!/bin/bash

./as11 -l sum.l -o sum.o $1
mv sum.o ../cmake-build-debug/sum.o
