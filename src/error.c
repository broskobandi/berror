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

/** \file include/error.c
 * \brief Implementation for the error library.
 * \details This file contains the definitions of public functions 
 * and global variables for the error library. */

#include "error_private.h"
#include <stdio.h>
#include <errno.h>

/** The global error object. */
_Thread_local static err_t g_err;

/** Global variable for storing error state. */
_Thread_local static int g_is_error_set;

/** Global variable for the test utility. */
int g_is_error_printed;

/** Sets the global error variable.
 * \param msg The error message. 
 * \param file The current file (query it with __FILE__).
 * \param func The current function (query it with __func__).
 * \param line The current line (query it with __LINE__). */
void error_set(
	const char *msg,
	const char *file,
	const char *func,
	int line)
{
	g_is_error_set = 1;
	g_err.msg = msg;
	g_err.file = file;
	g_err.func = func;
	g_err.line = line;
}

/** Prints the error information. */
void error_print() {
#ifndef NDEBUG
	g_is_error_printed = 1;
#else
	fprintf(stderr,
		"[ERROR]:\n\tMsg: %s\n\tFile: %s\n\tFunc: %s\n\tLine: %d\n",
		g_err.msg, g_err.file, g_err.func, g_err.line);
	if (errno) {
		perror("\tExtra info:");
	}
#endif
}

/** Checks if the error was set.
 * \return 0 if the error was not set and 1 if it was set. */
int error_is_set() {
	return g_is_error_set;
}

/** Returns a const pointer to the global error variable.
 * \return A pointer to the global error variable. */
const err_t *get_error() {
	return &g_err;
}
