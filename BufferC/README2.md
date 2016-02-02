# README
## Secure by Construction through Linguistic Abstraction

In this report design/implementation decisions are addressed:


### BufferC declaration:
BufferC declaration such as the following:

buffer b;

is managed by the run-time library, which allocates the buffers struct with size = 0;

This prevents it from being misused in the code at later stages.

All other assignments and creates are done via realloc. Realloc takes care of freeing previously used space on the heap.

e.g.

buffer a;
a = create(42);
a = create(420);

will have no memory leaks.

### Buffer Assignment:

Buffer Assignment such as *a = b* where both variables *a* and *b* are of type *Buffer()* copy *b* entirely into *a*;

Namely the following happens:
1. Memory previously allocated for *a* gets freed
2. *a* is mallocd with a new size corresponding to *b*
3. Contents of *a* are filled with contents from *b*

Hence, the state of *a* does not matter i.e. it's size nor content: an entirely new *a* is allocated and *b* is copied into *a*;


### Run-time failures

For run-time failures i.e. malloc failure, out of bounds exception etc. the program exits using the following:

exit(EXIT_FAILURE);

### .length operator

This operator returns the allocated buffer size.

### Reading from a file

We are assuming a really safe implemeanation of this, hence:

FILE * f = bufferc_fopen("input_file", "r");

rather than leaving it to the user to check wheterh opening the file was successful or not, we simply exit() if failed.

The C library function char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
