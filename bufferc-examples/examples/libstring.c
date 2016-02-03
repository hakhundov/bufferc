
#include <stdlib.h>
#include "buffer.h"
#include "libstring.h"
	
	
	buffer * str_copy(buffer * dst, buffer * src) {
	
	for(int i = 0; (i <  buf_size(src)); i++) {
			
			if((i <  buf_size(dst))) {
			  assign_char(dst, i, read_element(src, i));
			}
			
		}
	
	return dst;
	}
	
	buffer * str_clone(buffer * src) {
	buffer * dst = alloc_buf(buf_size(src));
	return str_copy(dst, src);
	}
	
	buffer * str_concat(buffer * s1, buffer * s2) {
	buffer * dst = alloc_buf((buf_size(s1) + buf_size(s2)));
	str_copy(dst, s1);
	
	for(int i = buf_size(s1); (i <  buf_size(dst)); i++) {
			
			if(((i - buf_size(s1)) <  buf_size(s2))) {
			  assign_char(dst, i, read_element(s2, (i - buf_size(s1))));
			}
			
		}
	
	return dst;
	}
	
	int chr_is_space(char c) {
	return ((c == '\32') || (c == '\t'));
	}
	
	buffer * str_trim(buffer * s) {
	int numLeadingSpaces = 0;
	int numTrailingSpaces = 0;
	int pos = 0;
	
	while(chr_is_space(read_element(s, pos))) {
		numLeadingSpaces++;
		pos++;
	}
	
	pos = (buf_size(s) - 1);
	
	while(chr_is_space(read_element(s, pos))) {
		numTrailingSpaces++;
		pos--;
	}
	
	buffer * dst = alloc_buf(((buf_size(s) - numLeadingSpaces) - numTrailingSpaces));
	
	for(int i = 0; (i <  buf_size(dst)); i++) {
			assign_char(dst, i, read_element(s, (i + numLeadingSpaces)));
		}
	
	return dst;
	}
	
	int str_equal(buffer * first, buffer * second) {
	
	if((buf_size(first) != buf_size(second))) {
	  return 0; 
	} else {
		
		for(int i = 0; (i <  buf_size(first)); i++) {
				
				if((read_element(first, i) != read_element(second, i))) {
				  return 0;
				}
				
			}
		
	}
	return 1;
	}
	
	int min(int a, int b) {
	if((a <  b)) return a; else return b;
	}
	
	int str_compare(buffer * s1, buffer * s2) {
	if(str_equal(s1, s2)) return 0;
	int diff = 0;
	
	for(int i = 0; (i <  min(buf_size(s1), buf_size(s2))); i++) {
			diff = (read_element(s1, i) - read_element(s2, i));
			if((diff >  0)) { return 1; } else 
			                              if((diff <  0)) {
			                                return -1;
			                              }
			                              
		}
	
	return 0;
	}
	
	void str_error(buffer * msg) {
	printf("ERROR: %s", msg->ptr);
	}
	
