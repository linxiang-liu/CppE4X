CC = g++
libcppe4x.so:*.o
	${CC} -shared -o libcppe4x.so *.o
*.o:*.cpp
	${CC} -fPIC -c *.cpp

default:libcppe4x.so

clean:
	rm -rf *.o
	rm -rf cppe4x.so
