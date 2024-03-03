
## Sqlite3 target for c++ compilation
# sqlite3CPP:
#	gcc -o sqlite3/sqlite3.o -c sqlite3/sqlite3.c

## Create main executable
tier: tier.cpp printtl.cpp
	g++ $^ sqlite3/sqlite3.o -o $@

## Remove executables
clean:
	rm -f *.exe