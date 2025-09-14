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

/** \file include/error_private.h 
 * \brief Private header file for the error library.
 * \details This file contains the definition of the error struct and 
 * declarations to aid the test utility. */

#ifndef ERROR_PRIVATE_H
#define ERROR_PRIVATE_H

#include "error.h"

/** Global variable for the test utility. */
extern int g_is_error_printed;

/** Struct for the global error information. */
typedef struct err {
	/** The error message. */
	const char *msg;

	/** The current file. */
	const char *file;

	/** The current function. */
	const char *func;

	/** The current line. */
	int line;
} err_t;

/** Returns a const pointer to the global error variable.
 * \return A pointer to the global error variable. */
const err_t *get_error();

#endif
