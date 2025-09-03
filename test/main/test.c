#include "test_error.h"

TEST_INIT;

int main(void) {
	test_error_set();
	test_error_print();
	test_error_get();
	test_error_reset();
	test_error_state();
	test_macros();

	test_print_results();
}
