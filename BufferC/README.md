# Secure by Construction through Linguistic Abstraction

The basic source code for this assignment can be found at

> https://github.com/MetaBorgCube/bufferc

In Lectures 2 and 3 we studied buffer overflow vulnerabilities, and discussed how these are caused by languages that do not enforce safety invariants. In this assignment, we study how classes of security vulnerabilities can be avoided by means of linguistic abstraction.

You should complete the implementation of ‘BufferC’, a small subset of the C programming language with a built-in safe buffer data type. The data type provides mutable ‘buffers’ (arrays) of characters with a length that is fixed at creation time. The length of a buffer is stored together with the buffer. The type system of the language ensures that buffers cannot be used other than through a small set of primitive operations. A correct implementation of these operations should ensure memory safety. That is, dynamic bounds checking should ensure that out of bound accesses (reads and writes) to buffers are caught. Automatic reference counting should ensure safe garbage collection that releases buffers when they are no longer used and avoids dangling pointers by not releasing buffers that are still in use.

## Base Implementation

We provide you with a basic implementation of BufferC consisting of:

- Syntax definition: Complete syntax of BufferC including buffer operations.
- Type system: The type system checks that BufferC programs are type correct, including the buffer operations.
- Code generator: The code generator translates the base language to the C language. This is mostly copying code that is the same in BufferC and C. 

These are wrapped in a language definition for the Spoofax Language Workbench, which produces an IDE with syntax and type checking.

## Assignment

Your task is to complete this basic implementation to a complete implementation of the language. This requires the following:

* Stage 1 (Minimal)
	- Code generation: To write code generation rules for the buffer operations
	- Run-time: Implement a run-time library buffer.c/buffer.h that provides an implementation of the primitive operations for buffers.
	- String library: Write a library `libstring.bc` in BufferC that implements a number of standard string operations 
	- Tests: Write test programs in BufferC to test the correct behavior of your implementation
* Stage 2 (For an 8)
	- Reference counting: Adapt code generation to realize reference counting garbage collection
* Stage 3 (For a 10)
	- Validate format strings
* Stage 4 (Super Bonus)
	- Optimizations

## Installing Software

#### Spoofax Language Workbench

Download the nightly build of the new Spoofax plugin (aka Spoofax Core):

> http://buildfarm.metaborg.org/job/spoofax-newplugin/lastSuccessfulBuild/artifact/dist/eclipse/

Download spoofax-os-arch-jre.zip that is suitable for the operating system and architecture of your computer. By choosing the `-jre` variant you get a compatible Java run-time.

This distribution is a complete Eclipse (Mars edition) with Spoofax and JRE installed and should run out of the box. 

#### CDT (optional)

To open generated C files and write new ones, it is convenient to install the C Development Tools (CDT) plugin for Eclipse. You can install the plugin from the Eclipse Marketplace, which you find in the `Help` menu:

> Help > Eclipse Marketplace

In the dialog search for CDT.

#### BufferC

You can find the base implementation of BufferC in the following git repository:

> https://github.com/MetaBorgCube/bufferc

* Make a local clone of the project. __Do not create a public fork of the repository.__ Your solution should not be published.

* In the downloaded Eclipse, import the directory as a Maven project.

* Build the project (Project menu) to make the language implementation active. 

* In the examples directory you find a couple of example `.bc` files. Open them to inspect what the IDE provides.

* Add the `Spoofax (Meta) Nature` to the project: right click on the project folder (in the explorer widget), 
	- spoofax (meta) -> add spoofax meta nature
	- spoofax -> add spoofax nature


## The BufferC Language

The ‘BufferC’ language is a very limited subset of the C language. It is not designed to make a complete usable language, but rather to be just big enough to illustrate the principles of linguistic abstraction for security.

* BufferC supports types int, boolean, char, FILE, and buffer. It does not support pointers, other array types, and user defined types using structs or unions.

* The language supports C-style function definitions with a return type and typed arguments.

* The language supports a selection of the common operators of C. Check syntax/Expressions.sdf3 for a complete overview 

### Buffer Data Type

The language has a built-in data type buffer with the following syntactic constructs:

    buffer a;             // built-in buffer type
    buffer b = create(5); // create empty buffer of length 5
    b = “abcdefgh”;       // buffer literal
    b[4];                 // indexed access
    b[4] = ‘a’;           // assignment
    print(b);             // print content of buffer
    printf(“b: %s\n”, b); // print with format string 
    b.length;             // length of string
    FILE f = fopen(“a”, “r”); // open file
    fread(b, f);          // read file into buffer

- `buffer` : the type of buffers
- `create(i)` : allocate a buffer of length i
- `“…”`: string literal returns buffer with 
- `b[i]` : (i+1)st character in buffer (0-based)
- `b[i] = c` : assign character c to (i+1)st character in buffer (0-based)
- `b.length` : length of the buffer 
- `print(b)` : print characters in b
- `printf(b0, b1, b2, …)` : print format string, using strings from bi to fill in `%s` placeholders format string is also a buffer
- `fread(b, file)` : read at most `b.length` characters from file into `b`

## Implementation

The git project that comes with this assignment contains a Spoofax project including a syntax definition, a type system, and a basic code generator. From this definition are generated a parser and type checker, and an IDE that uses these to check programs for syntactic and type correctness. The code generator translates BufferC programs into regular C programs. You should complete the implementation. There are increasing levels of completeness that you can attempt. Getting further gives you a higher grade.

## Libstring

As a first exercise in using BufferC, implement the functions in 

> examples/libstring.bc

## Buffer Operations (Minimal Requirement)

The first step is to write a C library to implement the primitive buffer operations. This code should go into the `buffer.h/c` files:

> examples/buffer.h
> examples/buffer.c

See the slides for a starting point.

Next you should define the `gen-c-special` code generation rules for the buffer constructs in

> trans/to-c/generate-safe.str

The rules are already listed. All you need to do is fill in the code pattern that you want to generate. Look for inspiration in

> trans/to-c/generate.str

which defines the code generation rules for the base language.

The run-time library and the code generation rules together should ensure a safe implementation of buffers in the sense that no out of bounds access should be possible. Since it is not possible to detect out of bound accesses statically it is fine if your code prints an error messages and exits with an error code in the case of an out of bounds access. Of course, proper BufferC code should be written defensively and not trigger such errors.

You should consider in your design how to treat 0 characters in buffers. Any reasonable solution is appropriate as long as it is consistent and safe. For example, you could consider using the C implementation of print/printf, but that should be consistent with your semantics for 0 characters.

Directory `examples/` contains a number of BufferC programs that you use as a starting point for testing your code generator. Use the 

> Spoofax > Syntax > Show abstract syntax

menu entry to get the abstract syntax tree for a program.

Invoke the code generator using the Generation menu:

> Spoofax > Generation > Generate C
> Spoofax > Generation > Generate C Header

## Reference Counting (For an 8)

The basic buffer operations allow us to create and modify buffers. However, when a buffer is no longer used the memory it uses should be released in order to be reused. The next stage of the assignment is to implement a simple reference counting garbage collector for BufferC that is safe. That is, BufferC programs have no memory leaks (retain memory that is no longer reachable) and no dangling pointers (caused by releasing buffers too soon).

Reference counting consists of keeping track of how many references exist to a buffer. This can be achieved by adding a reference count field to your buffer representation. Since buffers are simple data structures that can themselves contain pointers to other data, we are only concerned with references to buffers that are held in program variables. As long as one or more variables refer to a buffer, that buffer should not be freed. As soon as the reference count of a buffer decreases to zero, it is freed. 
See <http://www.brpreiss.com/books/opus5/html/page421.html> for a short explanation of reference counting with useful pictures.

We don’t want BufferC programmers to increment and decrement reference counts, since that is tediuos and error prone. Instead you should inject increment and decrement operations in the generated code. You can realize this injection by writing more `gen-c-special` rules in 

> trans/to-c/generate-safe.str

The webpage above gives a good explanation how to generate code for the assignment statement. But how about

- variable declarations
- passing buffers to functions
- returning buffers from functions
- buffers referred to by local variables
- etc.

Note that the transformation rules in 

> to-c/annotate-returns.str

annotate return statements with the variables that are in scope in the function. This is useful to consider the variales that go out of scope at a return statement.

## Format String Validation (For a 10)

The printf(fmt, s1, …, s2) primitive of BufferC takes a format string and a variable number of string arguments as argument. In the most general case, the format string can be a dynamically computed buffer. When translating this directly to C’s printf, this is vulnerable to user generated (or buggy) format strings. (See the Stanford paper about format string vulnerabilities.) A safe BufferC language rules out such vulnerabilities. In general a safe implementation should check that format string placeholders match with arguments of printf. And in the case that dynamic format strings are allowed, this check should be done at run-time, informed by the types of the other arguments of printf.

There are different levels of sophistication that you can consider for such a safe implementation:

- Require that the format string is a string literal (printf(“hello %s”, msg)) (by adapting the syntax definition) and that it only has whitelisted placeholders. Then, check that the number and types of arguments and placeholds match.
- Reduce the kinds of placeholders that are allowed
- Restrict printf to a fixed number of arguments (e.g. a format string and one buffer). 
- Dynamically validate the dynamically generated format string against the static knowledge of the types of the arguments. This requires generating an implementation of printf specialized for each call site and scanning the format string to match placeholders to arguments. 

In your report describe the decisions you have taken.

## Optimization (Bonus)

Dynamic checking is expensive. If we know statically that a buffer access is within bounds, we can leave out the dynamic check. If we can see all the uses of allocated memory, we can release that memory explicitly. (This is what C programmers do manually, but it is easy to make mistakes, which leads to vulnerabilities.) Based on static (data-flow) analysis, a compiler can make such optimizations safely (but perhaps too conservatively). Feel like a challenge? Consider how to optimize bounds checks, reference counting, or format string validation. I would be interested in any level of elaboration, from an example-driven explanation of how such an optimization would work, to peephole optimizations for specific cases, to a full-fledged analysis implemented in Stratego.

## Testing

Write test programs that test good behavior and potentially unsafe behavior. 

## Tips

* Sometimes static analysis gets stuck. Use ‘Clean Project’ in the   Project menu make a clean start.

## What to Submit

Submit a zip with your complete Spoofax project, including
* buffer.h, buffer.c: run-time system
* libstring.bc: library of string functions written in BufferC
* Code generation rules for buffer extension
* Code generation rules for reference count instrumentation
* Test programs for good and bad behavior
* README with your report which should in particular address any design/implementation decisions you have made

## Assessment

* Level 1: Correct code generation with bounds access checking (for a 5)
* Level 2: Reference counting (for an 8)
* Level 3: Format string validation (for a 10)
* Level 4: Optimization (for a 10+)


