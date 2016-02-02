#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

// This is the run-time library implementing the primitive operations for
// the BufferC buffer data type.

buffer *alloc_buf(int size) {
	buffer *buf = (buffer *)malloc(sizeof(buffer));
	if (buf == NULL) exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
	return buf; // unnecessary
}

buffer *copy(buffer *src) {
	buffer * dst = alloc_buf(src->bufsize);
	if (dst == NULL) exit(EXIT_FAILURE);
	assign_stringliteral(dst, src->ptr, src->bufsize);
	return dst;
}

int buf_size(buffer *buf) {
	return buf->bufsize;
}

//deprecated
int buf_length(buffer *buf){
	int len = 0;
		while (buf->ptr[len] != '\0') len++;
	return len;
}

char read_element(buffer *dst, int loc) {
	if (loc > dst->bufsize) {
		printf("Array index out of bounds");
		//exit(EXIT_FAILURE);
		return '\0'; //better to return NULL rather than terminate the program
	}
	else {
		return dst->ptr[loc];
	}
}

void assign_char(buffer *dst, int loc, char c) {
	if (loc >= dst->bufsize) {
		fprintf(stderr, "Array index out of bounds. line %d of file \"%s\" (function <%s>)\n", __LINE__, __FILE__, __func__);
		exit(EXIT_FAILURE);
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

// Print() with implicit new line
void bufferc_print(buffer * b) {
	printf("%s\n", b->ptr);
}

//This is not how we are going to do it yet
//TODO:
void bufferc_printf(char* format, buffer * b) {
	printf(format, b->ptr);
}


/* FILE OPERATIONS */
FILE * bufferc_fopen(char *fname, char *mode) {
	return fopen(fname, mode);
}

void bufferc_fread(buffer * b, FILE *fp) {
	fgets(b->ptr, b->bufsize, fp);
}

/* REFERENCE COUNTING */



