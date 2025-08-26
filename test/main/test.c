#include "test_berror.h"

BTEST_INIT;

int main(void) {
	test_berror_set();
	test_berror_print();

	btest_print_results();
}
