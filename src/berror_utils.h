#ifndef BERROR_UTILS_H
#define BERROR_UTILS_H

#include "berror.h"

extern _Thread_local berror_info_t g_err;

#ifdef TEST
extern int g_is_err_printed;
#endif

#endif
