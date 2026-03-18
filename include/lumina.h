#ifndef LUMINA_H
#define LUMINA_H

#include "stb_image.h"

typedef struct {
	const char* path;
	int width;
	int height;
	int channels;
	stbi_uc* data;
} LuImage;

LuImage lu_image_load(const char* image_path);
void lu_image_write(LuImage image);
void lu_log_image_info(LuImage image);

LuImage lu_enhance(LuImage input);
LuImage lu_blur(LuImage input);

#endif // LUMINA_H
