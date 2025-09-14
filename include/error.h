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
 * \brief Public header file for the error library.
 * \details This file contains the forward declarations of public functions 
 * and marco helpers for the error library. */

#include <stdlib.h>

#ifndef ERROR_H
#define ERROR_H

#define ERROR_SET(message)\
	error_set((message), __FILE__, __func__, __LINE__)

#define RET_ERR(message, ...)\
	do {\
		ERROR_SET((message));\
		return __VA_ARGS__;\
	} while(0)

#define RET_OK(...)\
	return __VA_ARGS__

#define TRY(function, error_code)\
	do {\
		(function);\
		if (error_is_set()) {\
			error_print();\
			exit((error_code));\
		}\
	} while(0)

/** Sets the global error variable.
 * \param msg The error message. 
 * \param file The current file (query it with __FILE__).
 * \param func The current function (query it with __func__).
 * \param line The current line (query it with __LINE__). */
void error_set(
	const char *msg,
	const char *file,
	const char *func,
	int line);

/** Prints the error information. */
void error_print();

/** Checks if the error was set.
 * \return 0 if the error was not set and 1 if it was set. */
int error_is_set();

#endif
