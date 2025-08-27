# berror
Threadsafe error handling tool for C.

## Features
- Threadlocal global error struct containing information about file, function, line, and a custom error message.
- The error information is retained until another process overrides it within the same thread.
- The print function calls perror implicitly, so an associated error message is also printed if errno is set by any of the standard libary functions.

## Installation
```bash
git clone https://github.com/broskobandi/berror.git &&
cd berror &&
make &&
sudo make install
```

## Uninstallation
```bash
cd berror &&
sudo make uninstall
```

## Testing
```bash
cd berror &&
make clean &&
make test &&
make clean
```

## Usage
```c
/* Include the library */
#include <berror.h>
#include <stdio.h>

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
		BERROR_SET("Failed to open file.");
		berror_print();
		return 1;
	}
	/* This will print:
		[ERROR]:
		File: example.c
		Func: main
		Line: 34
		Message: Failed to open file.
	Additional information: No such file or directory */

	return 0;
}
```
Don't forget to add -lberror to the compile command to link the library.
