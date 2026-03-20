#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include "nob.h"

bool lu_str_eq(const char* a, const char* b)
{
	return strcmp(a, b) == 0;
}

char* lu_add_ext(const char* path, const char* ext)
{
	const char* dot_ptr = strrchr(path, '.');
	size_t old_len      = 0;
	for (const char* path_ptr = path; *path_ptr && path_ptr != dot_ptr; path_ptr++) {
		old_len++;
	}

	size_t new_len = old_len + strlen(ext);
	char* buff     = calloc(new_len + 1, sizeof(char));
	if (buff == nullptr) {
		nob_log(NOB_ERROR, "Could not allocate %zu bytes: %s", new_len + 1, strerror(errno));
		exit(1);
	}

	memcpy(buff, path, old_len * sizeof(char));
	strcat(buff, ext);

	return buff;
}
