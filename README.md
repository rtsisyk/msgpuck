MsgPuck
=======

[![Travis][travis-badge]][travis-url]
[![License][license-badge]][license-url]
[![RPM Packages][rpm-badge]][rpm-url]
[![Debian Packages][deb-badge]][deb-url]
[![Telegram][telegram-badge]][telegram-url]
[![Maillist][groups-badge]][groups-url]

MsgPuck is a compact and efficient [MessagePack] serialization library:

 * Zero-cost abstractions and zero overhead
 * Clean and readable C code ready to use
 * Easy to incorporate into your project
 * Fully documented and covered by unit tests
 * Liberal license (BSD-2)

Status
------

MsgPuck is stable, which means it have been used in production without
serious bugs for quite a while now. The library is fully documented and
covered by unit tests.

Please feel free to file a ticket if your have a problem or a question.

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

You need a C89+ or C++03+ compatible compiler to use msgpuck.
Add this project as a submodule or just use libmsgpuck-dev package.

MsgPuck is designed to be fully embedded to your application by a C/C++
compiler. However, some functions require auxiliary static tables which
should be expanded somewhere in a compilation unit (`*.c` or `*.cc` file).
Please link libmsgpuck.a to your binary to avoid problems with unresolved
symbols.

See Also
--------

 * [API Documentation](http://rtsisyk.github.io/msgpuck/)
 * [Specification](https://github.com/msgpack/msgpack/blob/master/spec.md)
 * [Tests](test)
 * [Packages](https://tarantool.org/download.html)
 * [Maillist](https://groups.google.com/forum/#!forum/tarantool)
 * [Facebook](http://facebook.com/TarantoolDatabase/)
 * [Telegram Chat][telegram-url]
 * [Maillist][groups-url]

API documentation can be also generated using `make doc` (Doxygen is required).

MsgPuck was written to use within [Tarantool](http://tarantool.org) -
the world's first full-featured MsgPack-based database.

[MessagePack]: https://msgpack.org/
[travis-badge]: https://api.travis-ci.org/rtsisyk/msgpuck.svg?branch=master
[travis-url]: https://travis-ci.org/rtsisyk/msgpuck
[license-badge]: https://img.shields.io/badge/License-BSD--2-lightgray.svg?style=flat
[license-url]: LICENSE
[deb-badge]: https://img.shields.io/badge/Packages-Debian-red.svg?style=flat
[deb-url]: https://packagecloud.io/tarantool/1\_7?filter=debs
[rpm-badge]: https://img.shields.io/badge/Packages-RPM-blue.svg?style=flat
[rpm-url]: https://packagecloud.io/tarantool/1\_7?filter=rpms
[telegram-badge]: https://img.shields.io/badge/Telegram-join%20chat-blue.svg
[telegram-url]: http://telegram.me/tarantool
[groups-badge]: https://img.shields.io/badge/Google-Groups-orange.svg
[groups-url]: https://groups.google.com/forum/#!forum/tarantool
