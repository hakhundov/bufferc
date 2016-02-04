# README
----
## Secure by Construction through Linguistic Abstraction
*In this assignment, we study how classes of security vulnerabilities can be avoided by means of linguistic abstraction.*


### Running the tests

In order to run the tests, follow the steps:

1. <b>Generate C</b>  for *bufferc_tests.bc* & *libstring_tests.bc* using the <i>Spoofax</i> toolbar. 

	Note: 	(1) it might be necessary to remove the header files from the .c files containing the main()
			(2) Libraries might need to be generated too.

2. cd to /examples/tests/ directory and execute the *./run script*
	
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

buffer b;

is managed by the run-time library, which allocates the buffers struct with size = 0;

This prevents it from being misused in the code at later stages.

All other assignments and creates are done via realloc. Realloc takes care of freeing previously used space on the heap.

e.g.

##### Buffer Assignment:

Buffer Assignment such as *a = b* where both variables *a* and *b* are of type *Buffer()* copy *b* entirely into *a*;

Namely the following happens:
1. Memory previously allocated for *a* gets freed
2. *a* is mallocd with a new size corresponding to *b*
3. Contents of *a* are filled with contents from *b*

Hence, the state of *a* does not matter i.e. it's size nor content: an entirely new *a* is allocated and *b* is copied into *a*;


##### Run-time failures

For run-time failures i.e. malloc failure, out of bounds exception etc. the program exits using the following:

exit(EXIT_FAILURE);

##### .length operator

This operator returns the allocated buffer size.

##### Reading from a file

We are assuming a really safe implementation of this, hence:

FILE * f = bufferc_fopen("input_file", "r");

rather than leaving it to the user to check whether opening the file was successful or not, we simply exit() if failed.


#### libstring Library (libstring.bc)

No specific design or implementation decisions are made for this library. Function descriptions provided should be sufficient. 


#### Reference Counting

Certain memory management related aspects have already been taken care of using simply proper rewrite strategies and run-time libraries.

###### Example 1:

The following code snippet from *memoryleak.bc* <u>does not cause a memory leak</u>, since any subsequent creates use a *realloc*, which takes care of freeing the previously allocated buffer:

<b>BufferC</b>

		module memoryleak {
			void leak() { 
				buffer b;
				for(int i = 0; i < 1000000; i++) {
					b = create(100);
				}
			}
		}

The corresponding translation would be:

<b>C</b>

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

<b>Strategy</b>

		gen-c-special :
		Assign(Var(Identifier(var1)), Assign(), Var(Identifier(var2))) -> 
		$[ free([var1]);
		[var1] = copy([var2])]
		where
			<?Buffer()><get-type>var1
		;	<?Buffer()><get-type>var2

<b>BufferC</b>

		a = b;

<b>C</b>

		free(a);
		a = copy(b);

<b>This has a strong implication on the program, based on this assumption: No object is referenced from more than one pointer!</b>


Hence using the following strategy:

<b>Strategy</b>

		gen-c-special :
		    Assign(Var(Identifier(var1)) , Assign(), func_call) ->
		    $[ free([var1]);
			 [var1] = [func_call']]
			where
				func_call' := <genc>func_call
			;	<?Buffer()><get-type>var1
			; 	<?Buffer()><get-type>func_call

The following <b>BufferC</b> code:

		b = str_clone(a);
		
Translates into the following <b>C</b> code:

		free(b);
		b = str_clone(a);
	
<b>Hence we are preventing garbage altogether, by automatically freeing objects with no references.</b>



#### Format String Validation

A simple check is added for printf() safety: it ensures that the number of format specifiers in the format string matches the number of arguments.

A <b>Strategy</b> is defined such that it *wraps* the printf function, with a run-time function that checks format string before proceeding.

###### Example:

The following <b>BufferC</b> code:

		printf("%s %s", a, b);	
	
Translates into the following <b>C</b> code:

		if (printf_is_safe("%s %s",2))
		{
			printf("%s %s", a->ptr, b->ptr);
		}
		else
		{
			PRINTF_ERROR;
		};

*See buffer.c & buffer.h for printf_is_safe() and macro definitions*
