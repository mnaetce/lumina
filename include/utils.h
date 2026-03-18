#ifndef UTILS_H
#define UTILS_H

#define LU_UNIMPLEMENTED()                                                  \
	do {                                                                \
		nob_log(NOB_ERROR, "This feature is not implemented yet."); \
		exit(1);                                                    \
	} while (false)

#define LU_MAX(a, b) (((a) > (b)) ? (a) : (b))

bool lu_str_eq(const char* a, const char* b);
char* lu_add_ext(const char* path, const char* ext);

#endif // UTILS_H
