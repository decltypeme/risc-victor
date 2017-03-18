# risc-v
RISC-V Utilities


# Building All tools

```
chmod +x make-bin.sh
./make-bin.sh
```

# Generating Random Tests
```
chmod +x gen-rand-tests.sh
./gen-rand-tests.sh [tests-count] [min-prog-length] [max-prog-length]
```

# Assembler

## Compiling
```
g++ -std=c++11 assembler.cpp -o ../bin/assembler.o
chmod +x ../bin/assembler.o
```
## Usage
Options must be in the same order
```
./assembler.o source-file destination-file [--no-underscores]
```
# Rand-V

## Compiling
```
g++ -std=c++11 rand-v.cpp -o rand-v.o
chmod +x ../bin/rand-v.o
```
## Usage
Options must be in the same order
```
./rand-v.o files-count destination-dir [prog-min-length=17] [prog-max-length=42]
```
