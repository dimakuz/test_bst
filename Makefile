all: clean build test gcov

clean:
	rm -fr test inputs/ *.gcov *.gcda *.gcno
build: clean
	g++ -I../wet1 main.cpp -o test -g -fprofile-arcs -ftest-coverage
test: build
	./test.py | tee last | valgrind ./test
gcov: test
	gcov main.cpp
.PHONY: build test gcov clean
