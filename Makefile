CC = g++
FLAG = -std=c++11 -c -Wall -O3

all: read pos vel bnd exp fin
	$(CC) *.o -o _driven
read:
	$(CC) $(FLAG) import.cpp
ini:
	$(CC) $(FLAG) initialize.cpp 
pos:
	$(CC) $(FLAG) positions.cpp
vel:
	$(CC) $(FLAG) velocity.cpp
bnd:
	$(CC) $(FLAG) boundary.cpp
exp:
	$(CC) $(FLAG) export.cpp
fin:
	$(CC) $(FLAG) driven_cavity.cpp
clean:
	rm *.o _* *.out