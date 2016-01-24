#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

// This is the run-time library implementing the primitive operations for
// the BufferC buffer data type.

buffer *alloc_buf(int size) {
	buffer *buf = (buffer *)malloc(sizeof(buffer));
	buf->bufsize = size;
	buf->ptr = (char *) malloc(buf->bufsize + 1); // +1 for '\0'

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

char read_element(buffer *dst, int loc) {
	if (loc > dst->bufsize) {
		printf("Array index out of bounds");
		return '\0'; // TODO: return something else (?)
	}
	else {
		return dst->ptr[loc];
	}
}

void assign_char(buffer *dst, int loc, char c) {
	if (loc > dst->bufsize) {
		printf("Array index out of bounds");
	}
	else {
		dst->ptr[loc] = c;
	}
}


/* PRINTING */
void bufferc_printf(buffer b) {
	printf("%s", b->ptr);
}

/* FILE OPERATIONS */

/* REFERENCE COUNTING */



