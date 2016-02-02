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

MsgPuck is stable, which means it have been used in production without
serious bugs for quite a while now. The library is fully documented and
covered by unit tests.

Latest MsgPack specification (2013-09) is supported.
Please feel free to file a ticket if your have a problem or a question.

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

    const char *end = buf + xx;
    const char *b = buf;
    int rc = mp_check(&b, end);
    assert(rc == 0);
    assert(b == end);

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

Usage
-----

You need a C89+ or C++03+ compatible compiler to use msgpuck.h.
Add this project as a submodule or just copy  `msgpuck.h` to your project.

### Static Library

MsgPuck is designed to be fully embedded to your application by a C/C++
compiler. However, some functions require auxiliary static tables which
should be expanded somewhere in a compilation unit (`*.c` or `*.cc` file).
Please add libmsgpuck.a to your binary to avoid problems with unresolved
symbols.

### Just a Header

Include `msgpuck.h` as usual and define `MP_SOURCE 1` exactly in a single
compilation unit:

    #define MP_SOURCE 1 /* define in a single .c/.cc file */
    #include "msgpuck.h"

All non-inline versions of functions and global lookup tables will be
stored in the file. `MP_SOURCE` must be defined exactly in a single file of
your application, otherwise linker errors occur.

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
