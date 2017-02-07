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

#include "test.h"

#include <stdio.h>
#include <stdarg.h>

enum { MAX_LEVELS = 10 };
static int tests_done[MAX_LEVELS];
static int tests_failed[MAX_LEVELS];
static int plan_test[MAX_LEVELS];
static int level = -1;

void
__space(FILE *stream)
{
	for (int i = 0 ; i < level; i++) {
		fprintf(stream, "    ");
	}
}

void
plan(int count)
{
	++level;
	plan_test[level] = count;
	tests_done[level] = 0;
	tests_failed[level] = 0;

	__space(stdout);
	printf("%d..%d\n", 1, plan_test[level]);
}

int
check_plan(void)
{
	int r = 0;
	if (tests_done[level] != plan_test[level]) {
		__space(stderr);
		fprintf(stderr,
			"# Looks like you planned %d tests but ran %d.\n",
			plan_test[level], tests_done[level]);
		r = -1;
	}

	if (tests_failed[level]) {
		__space(stderr);
		fprintf(stderr,
			"# Looks like you failed %d test of %d run.\n",
			tests_failed[level], tests_done[level]);
		r = tests_failed[level];
	}
	--level;
	if (level >= 0) {
		is(r, 0, "subtests");
	}
	return r;
}

int
__ok(int condition, const char *fmt, ...)
{
	va_list ap;

	__space(stdout);
	printf("%s %d - ", condition ? "ok" : "not ok", ++tests_done[level]);
	if (!condition)
		tests_failed[level]++;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
	return condition;
}

