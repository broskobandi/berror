/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "berror_utils.h"
#include <stdio.h>
#include <errno.h>

_Thread_local berror_info_t g_err = {0};

void berror_set(berror_info_t err_info) {
	g_err = err_info;
}

#ifdef TEST
int g_is_err_printed = 0;
#endif

void berror_print() {
#ifndef TEST
	fprintf(stderr, "[ERROR]:\n\tFile: %s\n\tFunc: %s\n\tLine: %d\n\tMessage: %s\n",
			g_err.file, g_err.func, g_err.line, g_err.msg);
	if (errno)
		perror(NULL);
#else
	g_is_err_printed = 1;
#endif

}

berror_info_t berror_get() {
	return g_err;
}
