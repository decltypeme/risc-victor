#!/bin/bash
cd risc-c
for i in $(seq 1 3);
   do
      ./risc-c.sh ../tests/functional-tests/$i/c/$i.c ../tests/functional-tests/$i/lst/$i.lst
   done
