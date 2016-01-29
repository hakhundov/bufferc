CC=clang #gcc
CFLAGS=
#-I.
DEPS = buffer.h
OBJ = buffer.o simpler.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

simpler: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm *.o
