
#include <stdlib.h>
#include "buffer.h"
#include "simple.h"
	#include "libstring.h"
	
	void f() {
	buffer * b;
	b = alloc_buf(5);
	b = "bla";
	buf_length(b);
	buffer * a;
	a = b;
	assign_char(a, 0, 'a');
	int c = 42;
	assign_char(a, c, 'b');
	read_element(a, 0);
	Return("final"())
	}
	
