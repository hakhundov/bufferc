// buffer.h

// signatures for BufferC safe buffer data type

#ifdef BUFFER

#else

#define BUFFER 1

#include <stdio.h>
#include <string.h>

// buffer data type
typedef struct {
	char* ptr;
	int bufsize;
} buffer;

// prototypes of operations on buffer data type
buffer *alloc_buf(int size);
buffer *copy(buffer *src);
int buf_length(buffer *src);
#endif
