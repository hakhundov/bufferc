
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
	buffer_print(a);
	buffer_printf("%s %s", b);
	FILE * f = bufferc_fopen("a", "r");
	bufferc_fread(b, f);
	}
	
	int main() {
	f();
	return 0;
	}
	
