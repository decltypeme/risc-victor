# risc-v
RISC-V Utilities


# Building All tools

```
chmod +x make-bin.sh
./make-bin.sh
```

# Generating Random Tests
This will generate random tests, their results from the golden model.
```
chmod +x gen-rand-tests.sh
./gen-rand-tests.sh [tests-count=5] [min-prog-length=17] [max-prog-length=42]
```
The exact command that was fed to the CPU was
```
./gen-rand-tests.sh 5 7 10
```
# Assembling Functional Tests
```
chmod +x func-assemble-all.sh
./func-assemble-all.sh
```
# Assembler

## Compiling
```
g++ -std=c++11 src/assembler.cpp -o bin/assembler.o
chmod +x bin/assembler.o
```
## Usage
Options must be in the same order
```
./bin/assembler.o source-file destination-file [--disable-underscores]
```
# Rand-V

## Compiling
```
g++ -std=c++11 src/rand-v.cpp -o bin/rand-v.o
chmod +x bin/rand-v.o
```
## Usage
Options must be in the same order
```
./bin/rand-v.o files-count destination-dir [prog-min-length=17] [prog-max-length=42]
```
