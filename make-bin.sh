g++ -std=c++11 src/rand-v.cpp -o bin/rand-v.o
g++ -std=c++11 src/assembler.cpp -o bin/assembler.o
g++ -std=c++11 src/mem-bank-divide.cpp -o bin/mem-bank-divide.o
chmod +x bin/*.o
