/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** \file include/error.h
 * \details This file contains the public interface for the error library. */

#ifndef ERROR_H
#define ERROR_H

/** Struct to contain error information in. */
typedef struct error_info {
	const char *file;
	const char *func;
	const char *msg;
	int line;
} error_info_t;

/** Conveniently passes all the necessary information to error_set().
 * \param message The error message. */
#define ERROR_SET(message)\
	error_set((error_info_t){.file = __FILE__, .func = __func__, .msg = (message), .line = __LINE__})

/** Conveniently passes all the necessary information to error_set() and 
 * returns from the current function. Optionally, a return value can be passed 
 * if necessary. 
 * \param message The error message. 
 * \param ... The optional return value. Leave empty for void functions. */
#define RET_ERR(message, ...)\
	do {\
		ERROR_SET(message);\
		return __VA_ARGS__;\
	} while(0);

/** Returns from the current function. Optionally, a return value can be passed 
 * if necessary. This macro was made to create a uniform look in code where the 
 * ERR() macro is used.
 * \param message The error message. 
 * \param ... The optional return value. Leave empty for void functions. */
#define RET_OK(...)\
	return __VA_ARGS__

/** Experimental try catch pattern */
#define TRY(task, catch)\
	do {\
		do {\
			task\
		} while (0);\
		if (error_state()) {\
			do {\
				catch\
			} while (0);\
		}\
	} while(0);

/** Sets the thread-local global error object.
 * \param err_info The error information to be copied to the global error object. */
void error_set(const error_info_t err_info);
/** Prints the contents of the thread-local global error object. */
void error_print();
/** Returns the contents of the thrad-local global error object.
 * \return The error info. */
error_info_t error_get();
/** Clears the contents of the thread-local global error object. */
void error_reset();

/** Checks the global error state.
 * \return 0 if the global error is not set, 1 if it is set. */
int error_state();

#endif
