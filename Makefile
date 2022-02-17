CC=gcc
LIB_FLAGS=-fPIC -shared -g
CRITER_FLAGS=-g -L. -lMyFuncs
LIB_FILES=IO.c TEXT.c STRING.c
CRITER_FILES=criter.c
FINAL=criter

lib: $(LIB_FILES)
	$(CC) $(LIB_FLAGS) $(LIB_FILES) -o libMyFuncs.so 

criter: $(CRITER) $(LIB_FILES)
	make lib
	$(CC) $(CRITER_FLAGS) $(CRITER_FILES) -o $(FINAL)

test: $(FINAL)
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH
	./$(FINAL) test.txt

remove:
	rm *.so
