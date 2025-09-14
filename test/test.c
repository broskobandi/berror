#include "error_private.h"
#include <test.h>
#include <string.h>

TEST_INIT;

void test_error_set() {
	ASSERT(!error_is_set());
	ERROR_SET("msg");
	ASSERT(get_error()->line == __LINE__ - 1);
	ASSERT(!strcmp(get_error()->file, __FILE__));
	ASSERT(!strcmp(get_error()->func, __func__));
	ASSERT(!strcmp(get_error()->msg, "msg"));
	ASSERT(error_is_set());
}

void test_error_print() {
	ERROR_SET("msg");
	g_is_error_printed = 0;
	error_print();
	ASSERT(g_is_error_printed);
}

int main(void) {
	test_error_set();
	test_error_print();

	test_print_results();
	return 0;
}
