#include "test_berror.h"
#include "berror.h"
#include "berror_utils.h"
#include <string.h>

void test_berror_set() {
	memset(&g_err, 0, sizeof(berror_info_t));
	{ // Normal case
		BERROR_SET("msg");
		int line = __LINE__ - 1;
		BASSERT(!strcmp(g_err.msg, "msg"));
		BASSERT(!strcmp(g_err.file, __FILE__));
		BASSERT(!strcmp(g_err.func, __func__));
		BASSERT(g_err.line == line);
		memset(&g_err, 0, sizeof(berror_info_t));
	}
}

void test_berror_print() {
	memset(&g_err, 0, sizeof(berror_info_t));
	{ // Normal case
		g_is_err_printed = 0;
		BERROR_SET("msg");
		berror_print();
		BASSERT(g_is_err_printed == 1);
		memset(&g_err, 0, sizeof(berror_info_t));
	}
}

void test_berror_get() {
	memset(&g_err, 0, sizeof(berror_info_t));
	{ // Normal case
		berror_info_t src = {
			.msg = "msg",
			.file = __FILE__,
			.func = __func__,
			.line = __LINE__
		};
		berror_set(src);
		berror_info_t dst = berror_get();
		BASSERT(!memcmp(&src, &dst, sizeof(berror_info_t)));
		memset(&g_err, 0, sizeof(berror_info_t));
	}
}

void test_berror_reset() {
	memset(&g_err, 0, sizeof(berror_info_t));
	{ // Normal case
		berror_info_t empty = {0};
		berror_info_t src = {
			.msg = "msg",
			.file = __FILE__,
			.func = __func__,
			.line = __LINE__
		};
		berror_set(src);
		berror_info_t dst = berror_get();
		BASSERT(!memcmp(&src, &dst, sizeof(berror_info_t)));
		berror_reset();
		berror_info_t internal = berror_get();
		BASSERT(!memcmp(&internal, &empty, sizeof(berror_info_t)));
		memset(&g_err, 0, sizeof(berror_info_t));
	}
}
