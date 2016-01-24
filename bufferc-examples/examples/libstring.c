
#include <stdlib.h>
#include "buffer.h"
#include "libstring.h"
	
	
	int chr_is_space(char c) {
	return ((c == '\32') || (c == '\t'));
	Return("final"())
	}
	
	Buffer() str_copy(Buffer() dst, Buffer() src) {
	
	for(int i = 0; (i <  Field(src, Length())); i++) {
			
			if((i <  Field(dst, Length()))) {
			  ArrayField(dst, i) = ArrayField(src, i);
			}
			
		}
	
	return dst;
	Return("final"())
	}
	
	Buffer() str_clone(Buffer() src) {
	Buffer() dst = FunctionCall(Create(), (Field(src, Length())));
	return str_copy(dst, src);
	Return("final"())
	}
	
	Buffer() str_concat(Buffer() s1, Buffer() s2) {
	Buffer() dst = FunctionCall(Create(), ((Field(s1, Length()) + Field(s2, Length()))));
	str_copy(dst, s1);
	
	for(int i = Field(s1, Length()); (i <  Field(dst, Length())); i++) {
			
			if(((i - Field(s1, Length())) <  Field(s2, Length()))) {
			  ArrayField(dst, i) = ArrayField(s2, (i - Field(s1, Length())));
			}
			
		}
	
	return dst;
	Return("final"())
	}
	
	Buffer() str_trim(Buffer() s) {
	int numLeadingSpaces = 0;
	int numTrailingSpaces = 0;
	int pos = 0;
	
	while(chr_is_space(ArrayField(s, pos))) {
		numLeadingSpaces++;
		pos++;
	}
	
	pos = (Field(s, Length()) - 1);
	
	while(chr_is_space(ArrayField(s, pos))) {
		numTrailingSpaces++;
		pos--;
	}
	
	Buffer() dst = FunctionCall(Create(), (((Field(s, Length()) - numLeadingSpaces) - numTrailingSpaces)));
	
	for(int i = 0; (i <  Field(dst, Length())); i++) {
			ArrayField(dst, i) = ArrayField(s, (i + numLeadingSpaces));
		}
	
	return dst;
	Return("final"())
	}
	
	int str_equal(Buffer() first, Buffer() second) {
	
	if((Field(first, Length()) != Field(second, Length()))) {
	  return 0; 
	} else {
		
		for(int i = 0; (i <  Field(first, Length())); i++) {
				
				if((ArrayField(first, i) != ArrayField(second, i))) {
				  return 0;
				}
				
			}
		
	}
	return 1;
	Return("final"())
	}
	
	int str_compare(Buffer() s1, Buffer() s2) {
	int diff = 0;
	
	for(int i = 0; (i <  Field(s1, Length())); i++) {
			
			if((i <  Field(s2, Length()))) {
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
	
	void str_error(Buffer() msg) {
	FunctionCall(PrintF(), ("Omg errors: %s", msg));
	Return("final"())
	}
	
