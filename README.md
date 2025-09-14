# error
## Simple thread-safe error utility written in C.
The goal of the project is to provide convenient tools to save and retrieve 
error information.
## Features
### Performant thread safety
Thread safety is achieved without the use of mutex locks for increased 
performance.
### Convenient macro helpers
Function-like macros are provided for a streamlined syntax.
## Installation
```bash
git clone https://github.com/broskobandi/error.git &&
cd error &&
make &&
sudo make install
```
## Uninstallation
```bash
cd error &&
sudo make uninstall
```
## Testing
```bash
cd error &&
make clean &&
make test &&
make clean
```
## Documentation
For generating the documentation, ensure that Doxygen is installed.
```bash
cd error &&
make doc
```
Then open doc/html/index.html to view the generated documentation.
## Usage
```c
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
```
