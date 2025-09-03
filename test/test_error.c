#include "test_error.h"
#include "error.h"
#include "error_utils.h"
#include <string.h>

void test_error_set() {
	memset(&g_err, 0, sizeof(error_info_t));
	{ // Normal case
		ERROR_SET("msg");
		int line = __LINE__ - 1;
		ASSERT(!strcmp(g_err.msg, "msg"));
		ASSERT(!strcmp(g_err.file, __FILE__));
		ASSERT(!strcmp(g_err.func, __func__));
		ASSERT(g_err.line == line);
		memset(&g_err, 0, sizeof(error_info_t));
	}
}

void test_error_print() {
	memset(&g_err, 0, sizeof(error_info_t));
	{ // Normal case
		g_is_err_printed = 0;
		ERROR_SET("msg");
		error_print();
		ASSERT(g_is_err_printed == 1);
		memset(&g_err, 0, sizeof(error_info_t));
	}
}

void test_error_get() {
	memset(&g_err, 0, sizeof(error_info_t));
	{ // Normal case
		error_info_t src = {
			.msg = "msg",
			.file = __FILE__,
			.func = __func__,
			.line = __LINE__
		};
		error_set(src);
		error_info_t dst = error_get();
		ASSERT(!memcmp(&src, &dst, sizeof(error_info_t)));
		memset(&g_err, 0, sizeof(error_info_t));
	}
}

void test_error_reset() {
	memset(&g_err, 0, sizeof(error_info_t));
	{ // Normal case
		error_info_t empty = {0};
		error_info_t src = {
			.msg = "msg",
			.file = __FILE__,
			.func = __func__,
			.line = __LINE__
		};
		error_set(src);
		error_info_t dst = error_get();
		ASSERT(!memcmp(&src, &dst, sizeof(error_info_t)));
		error_reset();
		error_info_t internal = error_get();
		ASSERT(!memcmp(&internal, &empty, sizeof(error_info_t)));
		memset(&g_err, 0, sizeof(error_info_t));
	}
}

void test_error_state() {
	{ // Normal case
		error_reset();
		ASSERT(!error_state());
		ERROR_SET("message");
		ASSERT(error_state());
	}
}

void test_macros() {
	{ // ERROR_SET
		error_reset();
		ERROR_SET("msg");
		int line = __LINE__ - 1;
		ASSERT(g_err.line == line);
		ASSERT(!strcmp(g_err.msg, "msg"));
		ASSERT(!strcmp(g_err.file, __FILE__));
		ASSERT(!strcmp(g_err.func, __func__));
	}
	{ // TRY
		error_reset();
		TRY(
			int x = 5;
			if (x > 1) ERROR_SET("task failed.");
		,
			error_print()
		);
		ASSERT(error_state());
	}
}
