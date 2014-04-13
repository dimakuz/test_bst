all: clean build test gcov valgrind

clean:
	rm -fr test inputs/ *.gcov *.gcda *.gcno
build: clean
	g++ -I../wet1 main.cpp -o test -g -fprofile-arcs -ftest-coverage
test: build
	./run_tests.sh
gcov: test
	gcov main.cpp
valgrind: build
	./test.py 1000 | valgrind ./test
.PHONY: build test gcov valgrind
