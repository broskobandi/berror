/* Include the library. */
#include <error.h>

float divide(unsigned int a, unsigned int b) {
	/* Set the error code and return the specified error code... */
	if (b == 0) RET_ERR("b cannot be zero.", -1.0);

	/* ... or return the desired result. */
	RET_OK((float)a / (float)b);
}

int main(void) {
	/* Execute the function and exit with
	 * the specified error code on failure. */
	TRY(divide(10, 0), 1);

	return 0;
}

/* The program will print the following error and exit:
[ERROR]:
        Msg: b cannot be zero.
        File: example/example.c
        Func: divide
        Line: 6
 */
