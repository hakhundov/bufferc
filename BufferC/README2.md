# README
## Secure by Construction through Linguistic Abstraction

In this report design/implementation decisions are addressed:


### BufferC declaration:
BufferC decalartion such as the following:

buffer b;

is managed by the run-time library, which allocates the buffers struct with size = 0;

This prevents it from being misused in the code

### Buffer Assignment:

Buffer Assignment such as a = b where both a and b are of type Buffer() copy b entrirely into a;

The state of a does not matter i.e. it's size or content

and entirely new a is allocated and b is copied into a;


### Run-time failures

For run-time failures i.e. malloc failure, out of bounds exception etc. the program exits using the following:

exit(EXIT_FAILURE);

