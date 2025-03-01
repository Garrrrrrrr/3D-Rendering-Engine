# VAR:
CM = gcc
CFLAGS = -Wall -std=c99 -O2
LDFLAGS = -lm # math lib
OBJ = src/calc.o src/inputs.o src/spheres.o src/vector.o src/color.o src/assg.o

all: MS1_assg MS2_assg FS_assg

# Executables
MS1_assg: calc.o inputs.o spheres.o vector.o color.o assg.o
	$(CM) $(CFLAGS) $(OBJ) $(LDFLAGS) -o MS1_assg
	
MS2_assg: calc.o color.o inputs.o spheres.o vector.o assg.o
	$(CM) $(CFLAGS) $(OBJ) $(LDFLAGS) -o MS2_assg

FS_assg: calc.o color.o inputs.o spheres.o vector.o assg.o
	$(CM) $(CFLAGS) $(OBJ) $(LDFLAGS) -o FS_assg

# Object files
calc.o: src/calc.c
	$(CM) $(CFLAGS) -c src/calc.c -o src/calc.o

color.o: src/color.c
	$(CM) $(CFLAGS) -c src/color.c -o src/color.o

inputs.o: src/inputs.c
	$(CM) $(CFLAGS) -c src/inputs.c -o src/inputs.o

spheres.o: src/spheres.c
	$(CM) $(CFLAGS) -c src/spheres.c -o src/spheres.o

vector.o: src/vector.c
	$(CM) $(CFLAGS) -c src/vector.c -o src/vector.o

assg.o: src/assg.c
	$(CM) $(CFLAGS) -c src/assg.c -o src/assg.o -DFS

clean:
	rm -f src/*.o MS1_assg MS2_assg FS_assg
