CC = g++

cppe4xtest:main.o libcppe4x.so
	${CC} -o cppe4xtest main.o -L../CppE4X -lcppe4x

main.o:main.cpp
	${CC} -c main.cpp

default:cppe4xtest

libcppe4x.so:*.o
	make -C ../CppE4X

clean:
	${MAKE} -C ../CppE4X clean
	rm -rf main.o
	rm -rf libcppe4x.so
	rm -rf cppe4xtest.exe
	rm -rf cppe4xtest
