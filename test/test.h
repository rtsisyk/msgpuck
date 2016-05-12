/*
 * Copyright (C) 2010-2016 Tarantool AUTHORS:
 * please see AUTHORS file in tarantool/tarantool repository.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the
 *    following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * <COPYRIGHT HOLDER> OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <stdio.h>

/**
@brief example

@code
	#include "test.h"

	int main(void) {
		plan(3);		// count of test You planned to check
		ok(1, "Test name 1");
		is(4, 2 * 2, "2 * 2 == 4");
		isnt(5, 2 * 2, "2 * 2 != 5);
		return check_plan();	// print resume
	}
@endcode


*/

/* private function, use ok(...) instead */
int __ok(int condition, const char *fmt, ...);

/* private function, use note(...) or diag(...) instead */
void __space(FILE *stream);

#define msg(stream, ...) ({ __space(stream); fprintf(stream, "# ");            \
	fprintf(stream, __VA_ARGS__); fprintf(stream, "\n"); })

#define note(...) msg(stdout, __VA_ARGS__)
#define diag(...) msg(stderr, __VA_ARGS__)

/**
@brief set and print plan
@param count
Before anything else, you need a testing plan.  This basically declares
how many tests your program is going to run to protect against premature
failure.
*/
void plan(int count);

/**
@brief check if plan is reached and print report
*/
int check_plan(void);

#define ok(condition, fmt, args...)	{		\
	int res = __ok(condition, fmt, ##args);		\
	if (!res) {					\
		__space(stderr);			\
		fprintf(stderr, "#   Failed test '");	\
		fprintf(stderr, fmt, ##args);		\
		fprintf(stderr, "'\n");			\
		__space(stderr);			\
		fprintf(stderr, "#   in %s at line %d\n", __FILE__, __LINE__); \
	}						\
}

#define is(a, b, fmt, args...)	{			\
	int res = __ok((a) == (b), fmt, ##args);	\
	if (!res) {					\
		__space(stderr);			\
		fprintf(stderr, "#   Failed test '");	\
		fprintf(stderr, fmt, ##args);		\
		fprintf(stderr, "'\n");			\
		__space(stderr);			\
		fprintf(stderr, "#   in %s at line %d\n", __FILE__, __LINE__); \
	}						\
}

#define isnt(a, b, fmt, args...) {			\
	int res = __ok((a) != (b), fmt, ##args);	\
	if (!res) {					\
		__space(stderr);			\
		fprintf(stderr, "#   Failed test '");	\
		fprintf(stderr, fmt, ##args);		\
		fprintf(stderr, "'\n");			\
		__space(stderr);			\
		fprintf(stderr, "#   in %s at line %d\n", __FILE__, __LINE__); \
	}						\
}

#define fail(fmt, args...)		\
	ok(0, fmt, ##args)


#endif /* TEST_H_INCLUDED */

