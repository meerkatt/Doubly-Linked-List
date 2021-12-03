CXX=clang++
CXX_FLAGS=-std=c++20 -stdlib=libc++ -g -O0 -Wall -Wextra -Iincludes/

.PHONY: clean

driver: driver.o doubly_linked_list.o
	mkdir -p bin
	${CXX} ${CXX_FLAGS} -lc++abi obj/driver.o obj/doubly_linked_list.o -o bin/driver

driver.o: src/driver.cc doubly_linked_list.o includes/doubly_linked_list.hpp
	mkdir -p obj
	${CXX} ${CXX_FLAGS} -c src/driver.cc -o obj/driver.o

test: test.o doubly_linked_list.o
	mkdir -p bin
	${CXX} ${CXX_FLAGS} -lc++abi obj/test.o obj/doubly_linked_list.o -o bin/test

test.o: tests/catch.hpp tests/tests.cc includes/doubly_linked_list.hpp includes/node.hpp
	mkdir -p obj
	${CXX} ${CXX_FLAGS} -c tests/tests.cc -o obj/test.o

doubly_linked_list.o: includes/doubly_linked_list.hpp includes/node.hpp src/doubly_linked_list.cc
	mkdir -p obj
	${CXX} ${CXX_FLAGS} -c src/doubly_linked_list.cc -o obj/doubly_linked_list.o

clean:
	rm -f bin/*
