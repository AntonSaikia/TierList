FLAGS = -Wall -Werror -g -std=c++20

## Make build all
build: sqlite3CPP tier

## Sqlite3 target for c++ compilation
sqlite3CPP: sqlite3/sqlite3.c
	gcc -o sqlite3/sqlite3.o -c $^

## Create main executable
tier: tier.cpp printtl.cpp
	g++ $^ sqlite3/sqlite3.o $(FLAGS) -o $@

## Run target
run:
	tier

## Remove executables
clean:
	rm -f *.exe
