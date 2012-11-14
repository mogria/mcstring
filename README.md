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

function                                   | description
------------------------------------------:|:-------------------------------------------------
`mcstring *new_string(const char *init)`   | creates a string object out of the string `init`
`void free_string(mcstring *init)`         | frees the resources used by the string
