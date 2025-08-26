#include "test_berror.h"
#include "berror.h"
#include "berror_utils.h"
#include <string.h>

void test_berror_set() {
	memset(&g_err, 0, sizeof(berror_info_t));
	{ // Normal case
		BSET_ERR("msg");
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
		BSET_ERR("msg");
		berror_print();
		BASSERT(g_is_err_printed == 1);
		memset(&g_err, 0, sizeof(berror_info_t));
	}
}
