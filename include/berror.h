#ifndef BERROR_H
#define BERROR_H

typedef struct berror_info {
	const char *file;
	const char *func;
	const char *msg;
	int line;
} berror_info_t;

#define BSET_ERR(message)\
	berror_set((berror_info_t){.file = __FILE__, .func = __func__, .msg = (message), .line = __LINE__})

void berror_set(berror_info_t err_info);
void berror_print();

#endif
