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

buffer *realloc_buf(buffer * buf, int size) {
	char * temp;
	temp = realloc(buf->ptr, size+1);
	if (temp!=NULL){
		buf->ptr = temp;
		buf->bufsize = size;
	}
	else{
		//exit();
	}
	return buf; // unnecessary
}

buffer *copy(buffer *src) {
	buffer * dst = alloc_buf(src->bufsize);
	assign_stringliteral(dst, src->ptr);
	return dst;
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

void assign_stringliteral(buffer *dst, char* c, int length) {
	//sizeof is probably wrong
	int i;
	for(i = 0; i < length; i++) {
		if (i < dst->bufsize) {
			dst->ptr[i] = c[i];
		}
		else { // buffsize limit reached. breaking.
			break;
		}
	}
	dst->ptr[i] = '\0';
	//dst->ptr[(length < dst->bufsize)? length : dst->bufsize ] = '\0';
}


/* PRINTING */
void bufferc_printf(char* format, buffer b) {
	printf(format, b->ptr);
}

void bufferc_print(buffer b) {
	printf("%s", b->ptr);
}

/* FILE OPERATIONS */
FILE bufferc_fopen(char *fname, char *mode) {
	return fopen(fname, mode);
}

void bufferc_fread(buffer b, FILE *fp) {
	fgets(b->ptr, b->bufsize, fp);
}

/* REFERENCE COUNTING */



