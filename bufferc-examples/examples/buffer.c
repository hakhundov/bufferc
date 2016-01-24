#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

// This is the run-time library implementing the primitive operations for
// the BufferC buffer data type.

buffer *alloc_buf(int size) {
	buffer *buf = (buffer *)malloc(sizeof(buffer));
	buf->bufsize = size;
	buf->ptr = (char *) malloc(buf->bufsize);

	return buf;
}

buffer *copy(buffer *src) {
	buffer *dst = alloc_buf(src->bufsize);
	strncopy(dst->ptr, src-ptr, dst->bufsize);
	dst->ptr[dst->bufsize-1] = '\0';

	return buf;
}
int buf_length(buffer *src) {
	return buf->size;
}


/* PRINTING */
void bufferc_printf(buffer b) {
	printf("%s", b->ptr);
}

/* FILE OPERATIONS */

/* REFERENCE COUNTING */



