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
