CC = g++

cppe4xtest:main.o libcppe4x.a
	${CC} -o cppe4xtest main.o -L../CppE4X -lcppe4x

main.o:main.cpp
	${CC} -c main.cpp

default:cppe4xtest

libcppe4x.a:*.o
	make -C ../CppE4X

clean:
	${MAKE} -C ../CppE4X clean
	rm -rf main.o
	rm -rf libcppe4x.a
	rm -rf cppe4xtest.exe
	rm -rf cppe4xtest
