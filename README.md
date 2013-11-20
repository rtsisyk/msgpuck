MsgPuck
=======

MsgPuck is a simple and efficient [MsgPack](http://msgpack.org) binary
serialization library in a self-contained header file.

 * Can be easily incorporated into your project
 * Is very easy to use (see examples below)
 * Is fully tested and documented
 * Has clean and readable C source code
 * Is published under the very liberal license (BSD-2)

Status
------

MsgPuck is in beta stage.
Latest MsgPack specification (2013-09) is supported.

The library is fully documented and covered by unit tests.

[![Build Status](https://travis-ci.org/rtsisyk/msgpuck.png)]
(https://travis-ci.org/rtsisyk/msgpuck)

Examples
--------

**Encoding:**

    char buf[1024];

    char *w = buf;
    w = mp_encode_array(w, 4)
    w = mp_encode_uint(w, 10);
    w = mp_encode_str(w, "hello world", strlen("hello world"));
    w = mp_encode_bool(w, true);
    w = mp_encode_double(w, 3.1415);

**Validating:**

    const char *b = buf;
    bool is_valid = mp_check(&b);
    assert(is_valid);
    assert(b == w);

**Decoding:**

    uint32_t size;
    uint64_t ival;
    const char *sval;
    uint32_t sval_len;
    bool bval;
    double dval;

    const char *r = buf;
    size = mp_decode_array(&r);
    /* size is 4 */

    ival = mp_decode_uint(&r);
    /* ival is 10; */

    sval = mp_decode_str(&r, &sval_len);
    /* sval is "hello world", sval_len is strlen("hello world") */

    bval = mp_decode_bool(&r);
    /* bval is true */

    dval = mp_decode_double(&r);
    /* dval is 3.1415 */

    assert(r == w);

Installation
------------

You need a C99 or C++03 compatible compiler to use the header.

### Just use the header

Add this project as a git submodule or just copy  `msgpuck.h` to your project.
Include `msgpuck.h` as usual and define `MP_SOURCE 1` exactly in a single
compilation unit (`*.c` or `*.cc` file):

    #define MP_SOURCE 1 /* define in a single .c/.cc file */
    #include "msgpuck.h"

All non-inline versions of functions and global lookup tables will be 
stored in the file. `MP_SOURCE` must be defined exactly in a single compilation
unit in you application, otherwise linker errors occur.

### Compile as a shared library

You can also compile and install MsgPuck as a system-wide shared library:

    cmake .
    make
    make test
    make install

Include `msgpuck.h` and link your application with `-lmsgpuck`.

Documentation
-------------

 * [API Documentation](http://rtsisyk.github.io/msgpuck/)
 * [Specification](https://github.com/msgpack/msgpack/blob/master/spec.md)

API documentation can be also generated using `make doc` (Doxygen is required).

Contacts
--------

MsgPuck was written to use within [Tarantool](http://tarantool.org) -
the world's first full-featured MsgPack-based database.

 * roman@tsisyk.com

<img src="https://d2weczhvl823v0.cloudfront.net/rtsisyk/msgpuck/trend.png"
width="1px" height="1px" />
