#include "test_berror.h"

BTEST_INIT;

int main(void) {
	test_berror_set();
	test_berror_print();
	test_berror_get();
	test_berror_reset();

	btest_print_results();
}
