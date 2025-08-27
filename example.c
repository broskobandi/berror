/* Include the library */
#include <berror.h>

/* Find a fallible function. */
float divide(float dividend, float divisor) {
	/* Test a potentially erroneous value. */
	if (!divisor) {
		/* Set the error message and return from the function.
		 * This macro fills the global error object with useful
		 * addition information. */
		BERROR_SET("Divisor must not be 0.");
		return -1.0f;
		/* Optionally, this process can be achieved
		 * with just one macro call as well:
		 * ERR("Divisor must not be 0.", -1.0)*/
	}
	return dividend / divisor;
}

int main(int argc, char *argv[]) {
	/* Call the fallible function and test the result value. */
	if (divide(10, 0) == -1.0f) {
		/* Print the error information and return from the function. */
		berror_print();
		return 1;
	}

	return 0;
}
