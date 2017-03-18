#!/bin/bash
cd risc-c
for i in $(seq 1 3);
   do
      ./risc-c.sh ../tests/functional-tests/$i/c/$i.c ../tests/functional-tests/$i/lst/$i.lst
   done
cd ..
for i in $(seq 1 3);
   do
      xxd -r -p tests/functional-tests/$i/c/$i.c.v tests/functional-tests/$i/c/$i.bin
      ./bin/simulator.o tests/functional-tests/$i/c/$i.bin > tests/functional-tests/$i/result/res.txt
   done
