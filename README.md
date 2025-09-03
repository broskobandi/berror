# error
Threadsafe error handling tool for C.

## Features
- Threadlocal global error struct containing information about file, function, line, and a custom error message.
- The error information is retained until another process overrides it within the same thread.
- The print function calls perror implicitly, so an associated error message is also printed if errno is set by any of the standard libary functions.

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

## Usage
Please refer to example.c for details about usage.
Don't forget to add -L/usr/local/bin -lerror to the compile command to link the library.

## Generate documentation
This requires doxygen to be installed.
```bash
cd error &&
make doc
```
Then open the index.html file in doc/html to read the documentation.
