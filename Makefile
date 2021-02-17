CC=clang
DIR=MyFuncs

all: criter.c libMyFuncs
	$(CC) -o criter criter.c -L. -lMyFuncs

libMyFuncs: $(DIR)/IOFUNCS.c $(DIR)/STRING.c $(DIR)/WRITER.c
	$(CC) -o libMyFuncs.so -fPIC -shared $(DIR)/IOFUNCS.c $(DIR)/STRING.c $(DIR)/WRITER.c -lc

remove:
	rm *.o