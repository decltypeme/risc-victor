#!/bin/bash
TESTCOUNT=${1:-5}
MINLENGTH=${2:-17}
MAXLENGTH=${3:-42}
./bin/rand-v.o $TESTCOUNT tests/rand-tests $MINLENGTH $MAXLENGTH
for i in $(seq 1 $TESTCOUNT);
   do
     ./bin/assembler.o tests/rand-tests/rand_$i/rand_$i.s tests/rand-tests/rand_$i/rand_$i.lst --disable-underscores
     ./bin/assembler.o tests/rand-tests/rand_$i/rand_$i.s tests/rand-tests/rand_$i/rand_$i.lst_
     ./bin/mem-bank-divide.o tests/rand-tests/rand_$i/rand_$i.lst
     ./bin/binhex.o tests/rand-tests/rand_$i/rand_$i.lst
      xxd -r -p tests/rand-tests/rand_$i/rand_$i.lst.hex tests/rand-tests/rand_$i/rand_$i.bin
      mkdir tests/rand-tests/rand_$i/results
      ./bin/simulator.o tests/rand-tests/rand_$i/rand_$i.bin > tests/rand-tests/rand_$i/results/golden.txt
   done
