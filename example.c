#include <stdio.h>

/* Include the library */
#include <error.h>

/* Find a fallible function. */
float divide(int dividend, int divisor) {
	/* Test a potentially erroneous value. */
	if (!divisor) {
		/* Set the error message and return from the function.
		 * This macro fills the global error object with useful
		 * addition information. */
		ERROR_SET("Divisor must not be 0.");
		return -1.0f;
		/* Optionally, this process can be achieved
		 * with just one macro call as well:
		 * RET_ERR("Divisor must not be 0.", -1.0)*/
	}
	return ((float)dividend / (float)divisor);
	/* Optionally, this process can be achieved 
	 * by calling RET_OK(<return_value>) if you prefer a uniform look. */
}

int main(void) {
	/* Call the fallible function and test the result value. */
	if (divide(10, 0) == -1.0f) {
		/* Print the error information and return from the function. */
		error_print();
		return 1;
	}
	/* This will print:
		[ERROR]:
		File: example.c
		Func: divide
		Line: 13
		Message: Divisor must not be 0. */

	/* If calling a function that sets the standard errno,
	 * that information will also be printed. */
	FILE *file = fopen("some_file_that_does_not_exist", "r");
	if (!file) {\
		ERROR_SET("Failed to open file.");
		error_print();
		return 1;
	}
	/* This will print:
		[ERROR]:
		File: example.c
		Func: main
		Line: 34
		Message: Failed to open file.
	Additional information: No such file or directory */

	/* On top of this, a try-catch-like pattern is provided for functions 
	 * or other tasks that may set the error state internally but do not
	 * indicate success through a return value. */
	TRY(
		// Some task to try
		int x = 5;
		if (x > 1)
			ERROR_SET("X is too big.");
		// Or a void function that sets the error state internally.
	,
		// To be executed if the error state was set
		error_print();
		return 1;
	)

	return 0;
}
