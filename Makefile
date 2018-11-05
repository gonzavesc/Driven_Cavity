CC = g++
FLAG = -std=c++11 -c -Wall -O3

all: read pos vel bnd exp uti poss fin
	$(CC) -O3 *.o -o _driven
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
uti:
	$(CC) $(FLAG) util.cpp
poss:
	$(CC) $(FLAG) poiss.cpp
fin:
	$(CC) $(FLAG) driven_cavity.cpp
clean:
	rm *.o _* *.out Results/*.out