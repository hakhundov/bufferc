
#include <stdlib.h>
#include "buffer.h"
#include "simple.h"
	#include "libstring.h"
	
	void f() {
	buffer * a;
	a = alloc_buf(0);
	realloc_buf(a, 5);
	buffer * b = alloc_buf(5);
	assign_stringliteral(b, "bla", 3);
	free(a);
	a = copy(b);
	bufferc_print(a);
	bufferc_print(b);
	bufferc_printf();
	Return("final"())
	}
	
	int main() {
	f();
	return 0;
	Return("final"())
	}
	
