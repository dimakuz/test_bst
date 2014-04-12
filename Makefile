all: clean build test gcov

clean:
	rm -fr test inputs/ *.gcov *.gcda *.gcno
build:
	g++ -I../wet1 main.cpp -o test -g -fprofile-arcs -ftest-coverage
test:
	./run_tests.sh
gcov:
	gcov main.cpp
.PHONY: build test gcov
