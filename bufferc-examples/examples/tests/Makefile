CC=clang #gcc
CFLAGS=
#-I.
DEPS = buffer.h
OBJ = buffer.o bufferc_tests.o 


%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

test_bufferc: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm *.o
	rm test_bufferc
