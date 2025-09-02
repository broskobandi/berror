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

/** \file src/error_utils.h
 * \details This file contains the implementation of the error library. */

#include "error_utils.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

/** Thread local global error object. */
_Thread_local error_info_t g_err = {0};

/** Thread local global error state */
_Thread_local int g_is_err_set = 0;

/** Sets the global error object.
 * \param err_info The error information to be copied to the global error object. */
void error_set(const error_info_t err_info) {
	g_is_err_set = 1;
	g_err = err_info;
}

#ifdef TEST
/** Variable used to test the error_print() function. */
int g_is_err_printed = 0;
#endif

/** Prints the contents of the global error object. */
void error_print() {
#ifndef TEST
	fprintf(stderr, "[ERROR]:\n\tFile: %s\n\tFunc: %s\n\tLine: %d\n\tMessage: %s\n",
			g_err.file, g_err.func, g_err.line, g_err.msg);
	if (errno)
		perror("Additional information");
#else
	g_is_err_printed = 1;
#endif

}

/** Returns the contents of the thrad-local global error object.
 * \return The error info. */
error_info_t error_get() {
	return g_err;
}

/** Clears the contents of the thread-local global error object. */
void error_reset() {
	memset(&g_err, 0, sizeof(error_info_t));
	g_is_err_set = 0;
}

/** Checks the global error state.
 * \return 0 if the global error is not set, 1 if it is set. */
int error_state() {
	return  g_is_err_set;
}
