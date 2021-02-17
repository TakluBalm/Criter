CC=clang

all: criter.c libMyFuncs
	$(CC) -o criter criter.c -L. -lMyFuncs

libMyFuncs: IOFUNCS.c STRING.c WRITER.c
	$(CC) -o libMyFuncs.so -fPIC -shared IOFUNCS.c STRING.c WRITER.c -lc

remove:
	rm *.o