CC = g++
libcppe4x.a:*.o
	ar rcs libcppe4x.a *.o
*.o:*.cpp
	${CC} -c *.cpp

default:libcppe4x.a

clean:
	rm -rf *.o
	rm -rf libcppe4x.a
