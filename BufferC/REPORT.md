# README
----
## Secure by Construction through Linguistic Abstraction
*In this assignment, we study how classes of security vulnerabilities can be avoided by means of linguistic abstraction.*


### Running the tests

In order to run the tests, follow the steps:

1. **Generate C**  for *bufferc_tests.bc* & *libstring_tests.bc* using the *Spoofax* toolbar. 
    
    Note: 	(1) it might be necessary to remove the header files from the .c files containing the main()
			(2) Libraries might need to be generated too.

2. cd to /examples/tests/ directory and execute the \*./run script*
	
	The script does the following:

		1. Copies all the necessary library files into the current directory
		2. Cleans the directory
		3. Makes bufferc_tests and runs them
		4. Makes libstring_tests and runs them


    Note:
	The Makefile uses clang. Modify CC var in both makefiles as needed.

#### Run-Time Library (bufferc.c)

In this section some important design & implementation decisions are addressed:

##### BufferC declaration:
BufferC declaration such as the following:

`buffer b;`

is managed by the run-time library, which allocates the buffers struct with size = 0;

This prevents it from being misused in the code at later stages.

All other assignments and creates are done via realloc. Realloc takes care of freeing previously used space on the heap.

e.g.

##### Buffer Assignment:

Buffer Assignment such as *a = b* where both variables *a* and *b* are of type `Buffer()` copy *b* entirely into *a*;

Namely the following happens:
1. Memory previously allocated for *a* gets freed
2. *a* is `malloc`'d with a new size corresponding to *b*
3. Contents of *a* are filled with contents from *b*

Hence, the state of *a* does not matter i.e. it's size nor content: an entirely new *a* is allocated and *b* is copied into *a*;


##### Run-time failures

For run-time failures i.e. `malloc` failure, out of bounds exception etc. the program exits using the following:

`exit(EXIT_FAILURE);`

##### .length operator

This operator returns the allocated buffer size.

##### Reading from a file

We are assuming a really safe implementation of this, hence:

`FILE * f = bufferc_fopen("input_file", "r");`

rather than leaving it to the user to check whether opening the file was successful or not, we simply `exit()` if failed.


#### libstring Library (libstring.bc)

No specific design or implementation decisions are made for this library. Function descriptions provided should be sufficient. 


#### Reference Counting

Certain memory management related aspects have already been taken care of using simply proper rewrite strategies and run-time libraries.

###### Example 1:

The following code snippet from *memoryleak.bc* <u>does not cause a memory leak</u>, since any subsequent creates use a *realloc*, which takes care of freeing the previously allocated buffer:

**BufferC**

		module memoryleak {
			void leak() { 
				buffer b;
				for(int i = 0; i < 1000000; i++) {
					b = create(100);
				}
			}
		}

The corresponding translation would be:

**C**

		void leak() {
			buffer * b;
			b = alloc_buf(0);
			
			for(int i = 0; (i <  1000000); i++) {
					b = realloc_buf(b,100);
				}
		}
*See buffer.c for more on function definitions*

###### Example 2:

As stated in the sections above, one of the assumption about the assignment operator is that the entire structure gets allocated and copied in the previous pointer. Memory management is intrinsically taking place here as well.

**Strategy**

		gen-c-special :
		Assign(Var(Identifier(var1)), Assign(), Var(Identifier(var2))) -> 
		$[ free([var1]);
		[var1] = copy([var2])]
		where
			<?Buffer()><get-type>var1
		;	<?Buffer()><get-type>var2

**BufferC**

		a = b;

**C**

		free(a);
		a = copy(b);

**This has a strong implication on the program, based on this assumption: No object is referenced from more than one pointer!**


Hence using the following strategy:

**Strategy**

		gen-c-special :
		    Assign(Var(Identifier(var1)) , Assign(), func_call) ->
		    $[ free([var1]);
			 [var1] = [func_call']]
			where
				func_call' := <genc>func_call
			;	<?Buffer()><get-type>var1
			; 	<?Buffer()><get-type>func_call

The following **BufferC** code:

		b = str_clone(a);
		
Translates into the following **C** code:

		free(b);
		b = str_clone(a);
	
**Hence we are preventing garbage altogether, by automatically freeing objects with no references.**

*Return statements are annotated, and all allocated buffers (except the one being returned from a function) are freed just before returning.*


#### Format String Validation

A simple check is added for `printf()` safety: it ensures that the number of format specifiers in the format string matches the number of arguments.

A **Strategy** is defined such that it *wraps* the printf function, with a run-time function that checks format string before proceeding.

###### Example:

The following **BufferC** code:

		printf("%s %s", a, b);	
	
Translates into the following **C** code:

		if (printf_is_safe("%s %s",2))
		{
			printf("%s %s", a->ptr, b->ptr);
		}
		else
		{
			PRINTF_ERROR;
		};

*See buffer.c & buffer.h for `printf_is_safe()` and macro definitions*

Note that in general modern C compilers (gcc, clang) would also give a compile-time warning (that is if the appropriate compiler warnings are enabled) when printf() is misused such as:

	bufferc_tests.c:244:70: warning: format specifies type 'char *' but the argument
	      has type 'int' [-Wformat]
	  ...printf("%s! The answer to life, universe and everything is: %d\n", a);
	             ~~                                                         ^
	             %d
	bufferc_tests.c:244:64: warning: more '%' conversions than data arguments
	      [-Wformat]

