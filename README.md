mcstring
========

Immutable string library for C. 

compiling
---------

You need to have [cmake](http://cmake.org) to build the project.

    $ git clone git://github.com/mogria/mcstring.git
    $ cd mcstring
    $ cmake .
    $ make

now you should find `libmcstring.a` (or similar) in your current directory.
Simply add `-lmcstring` to your linker options and move the library file to an
location searched by the linker (e.g. `/usr/lib`). You'll also need the headers
to let your application know what functions are inside of the library file. To
do so simply add the files in `include/` to your include directories or copy the
  files over to your project.

library functions
-----------------

function                                                             | description
--------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------
`mcstring *new_string(const char *init)`                             | creates a string object by copying `init`
`mcstring *wrap_string(const char *init)`                            | creates a string object by using  `init` without copying it
`void free_string(mcstring *string)`                                 | frees the resources used by the string
`const mcchar *string_data(mcstring *string)`                        | returns the interal data array of the string (not null terminated)
`size_t string_size(mcstring *string)`                               | returns the size of the string
`mcchar *c_string(mcstring *string)`                                 | get a copy of the contents of the string as a null terminated c string allocated using `malloc()`
`void copy_string(char *dest, mcstring *src, size_t destsize)`       | get a copy of the contents of the string into your buffer
`mcstring *sub_string(mcstring *string, size_t offset, size_t size)` | get a part of a string as `mcstring *`
`mcchar char_string(mcstring *string, int pos)`                      | get a single char of the string in the position `pos`
`mcstring *reverse_string(mcstring *string)`                         | get the reverse of the string as `mcstring *`
`mcstring *ltrim_string(mcstring *string, const char *chars)`        | remove chars in front of the string
`mcstring *rtrim_string(mcstring *string, const char *chars)`        | remove chars at the end of the string
`mcstring *trim_string(mcstring *string, const char *chars)`         | remove chars in front and at the end of the string
`void write_string(FILE *file, mcstring *string)`                    | write the string to a file
`void print_string(mcstring *string)`                                | output the string to `stdout`


