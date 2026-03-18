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
	size_t old_len = strlen(path);
	size_t new_len = old_len + strlen(ext);
	char* buff     = calloc(new_len + 1, sizeof(char));
	if (buff == nullptr) {
		nob_log(NOB_ERROR, "Could not allocate %zu bytes: %s", new_len + 1, strerror(errno));
		exit(1);
	}

	strcpy(buff, path);
	strcat(buff, ext);

	return buff;
}
