CC = g++
FLAG = -std=c++11 -c -Wall -O3

all: read fin
	$(CC) *.o -o _driven
read:
	$(CC) $(FLAG) import.cpp
ini:
	$(CC) $(FLAG) initialize.cpp 
exp:
	$(CC) $(FLAG) export.cpp
metho:
	$(CC) $(FLAG) method.cpp
bnd:
	$(CC) $(FLAG) boundary.cpp
gss:
	$(CC) $(FLAG) gauss.cpp
fin:
	$(CC) $(FLAG) driven_cavity.cpp
clean:
	rm *.o