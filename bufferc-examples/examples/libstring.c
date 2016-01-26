
#include <stdlib.h>
#include "buffer.h"
#include "libstring.h"
	
	
	int chr_is_space(char c) {
	return ((c == '\32') || (c == '\t'));
	Return("final"())
	}
	
	buffer * str_copy(buffer * dst, buffer * src) {
	
	for(int i = 0; (i <  buf_length(src)); i++) {
			
			if((i <  buf_length(dst))) {
			  assign_char(dst, i, read_element(src, i));
			}
			
		}
	
	return dst;
	Return("final"())
	}
	
	buffer * str_clone(buffer * src) {
	buffer * dst = alloc_buf(buf_length(src));
	return str_copy(dst, src);
	Return("final"())
	}
	
	buffer * str_concat(buffer * s1, buffer * s2) {
	buffer * dst = alloc_buf((buf_length(s1) + buf_length(s2)));
	str_copy(dst, s1);
	
	for(int i = buf_length(s1); (i <  buf_length(dst)); i++) {
			
			if(((i - buf_length(s1)) <  buf_length(s2))) {
			  assign_char(dst, i, read_element(s2, (i - buf_length(s1))));
			}
			
		}
	
	return dst;
	Return("final"())
	}
	
	buffer * str_trim(buffer * s) {
	int numLeadingSpaces = 0;
	int numTrailingSpaces = 0;
	int pos = 0;
	
	while(chr_is_space(read_element(s, pos))) {
		numLeadingSpaces++;
		pos++;
	}
	
	pos = (buf_length(s) - 1);
	
	while(chr_is_space(read_element(s, pos))) {
		numTrailingSpaces++;
		pos--;
	}
	
	buffer * dst = alloc_buf(((buf_length(s) - numLeadingSpaces) - numTrailingSpaces));
	
	for(int i = 0; (i <  buf_length(dst)); i++) {
			assign_char(dst, i, read_element(s, (i + numLeadingSpaces)));
		}
	
	return dst;
	Return("final"())
	}
	
	int str_equal(buffer * first, buffer * second) {
	
	if((buf_length(first) != buf_length(second))) {
	  return 0; 
	} else {
		
		for(int i = 0; (i <  buf_length(first)); i++) {
				
				if((read_element(first, i) != read_element(second, i))) {
				  return 0;
				}
				
			}
		
	}
	return 1;
	Return("final"())
	}
	
	int str_compare(buffer * s1, buffer * s2) {
	int diff = 0;
	
	for(int i = 0; (i <  buf_length(s1)); i++) {
			
			if((i <  buf_length(s2))) {
			  diff = 0;
			  if((diff >  0)) { return 1; } else 
			                                if((diff <  0)) {
			                                  return -1;
			                                }
			                                
			}
			
		}
	
	return 0;
	Return("final"())
	}
	
	void str_error(buffer * msg) {
	buffer_printf("Omg errors: %s", msg);
	Return("final"())
	}
	
