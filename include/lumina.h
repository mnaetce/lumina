#ifndef LUMINA_H
#define LUMINA_H

#include "stb_image.h"

// LuImage is a 3D Tensor of shape [height, width, channels]
typedef struct {
	// File Path
	const char* path;

	// Dimensions
	int height, width, channels;

	// Strides
	int stry, strx, strc;

	// Data
	int count;
	stbi_uc* data;
} LuImage;

LuImage lu_image_load(const char* image_path);
void lu_image_write(LuImage image);
void lu_image_log_info(LuImage image);

LuImage lu_enhance(LuImage input, float scale);
LuImage lu_blur(LuImage input, int radius);
LuImage lu_arithmetic_mean_filter(LuImage input);
LuImage lu_geometric_mean_filter(LuImage input);

#endif // LUMINA_H
