// buffer.h
// signatures for BufferC safe buffer data type

#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <string.h>

#define PRINTF_ERROR fprintf(stderr, "Error in printf! Number of arguments doesn't math specifiers. line %d of file \"%s\" (function <%s>)\n", __LINE__, __FILE__, __func__);\
		exit(EXIT_FAILURE);

// BufferC data type
typedef struct {
	char* ptr;
	int bufsize;
	// int ref_count; //this is unnecessary; explained in the REPORT
} buffer;


// prototypes of operations on buffer data type

buffer *alloc_buf(int size);
buffer *realloc_buf(buffer * buf, int size);
buffer *copy(buffer *src);
int buf_length(buffer *buf);
int buf_size(buffer *buf);
char read_element(buffer *dst, int loc);
void assign_char(buffer *dst, int loc, char c);
void assign_stringliteral(buffer *dst, char* c, int length);
void bufferc_printf(char* format, buffer * b);
void bufferc_print(buffer * b);
FILE * bufferc_fopen(char *fname, char *mode);
void bufferc_fread(buffer * b, FILE *fp);
int printf_is_safe(char * format, int arg_count);

#endif
