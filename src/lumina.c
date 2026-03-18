#include "lumina.h"
#include "nob.h"
#include "utils.h"
#include "stb_image_write.h"

LuImage lu_image_load(const char* image_path)
{
	nob_log(NOB_INFO, "Loading %s", image_path);
	FILE* image_file = fopen(image_path, "rb");
	if (image_file == nullptr) {
		nob_log(NOB_ERROR, "Could not open file %s for reading: %s", image_path, strerror(errno));
		exit(1);
	}

	LuImage image = { 0 };
	image.path    = image_path;
	image.data    = stbi_load_from_file(image_file, &image.width, &image.height, &image.channels, 3);
	fclose(image_file);

	if (image.data == nullptr) {
		nob_log(NOB_INFO, "stb_image could not load image %s: %s", image_path, stbi_failure_reason());
		exit(1);
	}

	lu_log_image_info(image);
	return image;
}

void lu_image_write(LuImage image)
{
	nob_log(NOB_INFO, "Writing %s", image.path);
	lu_log_image_info(image);
	int result = stbi_write_jpg(image.path, image.width, image.height, image.channels, image.data, 100);
	if (result == 0) {
		nob_log(NOB_ERROR, "stb_image_write could not write file %s", image.path);
		exit(1);
	}
}

void lu_log_image_info(LuImage image)
{
	nob_log(NOB_INFO, "width = %d", image.width);
	nob_log(NOB_INFO, "height = %d", image.height);
	nob_log(NOB_INFO, "channels = %d", image.channels);
}

LuImage lu_enhance(LuImage input)
{
	if (input.channels != 3) {
		nob_log(NOB_ERROR, "We currently only support 3-channel RGB image enchancing");
		exit(1);
	}

	size_t n       = input.width * input.height * input.channels;
	LuImage output = {
		.path     = lu_add_ext(input.path, ".jpg"),
		.width    = input.width,
		.height   = input.height,
		.channels = input.channels,
		.data     = calloc(n, sizeof(input.data[0])),
	};

	if (output.data == nullptr) {
		nob_log(NOB_ERROR, "Could not allocate %zu bytes: %s", n, strerror(errno));
		exit(1);
	}

	nob_log(NOB_INFO, "Enhancing %s", input.path);

	for (size_t i = 0; i < n; ++i) {
		// Normalize to [-0.5, 0.5]
		float norm = (float)input.data[i] / 255.0f - 0.5f;

		// scale and clip
		float scale = 1.5f;
		norm *= scale; // [-scale * 0.5, scale * 0.5];
		if (norm < -0.5f) norm = -0.5f;
		if (norm > +0.5f) norm = +0.5f;

		// denormalize and clip
		int byte = (norm + 0.5f) * 255.0f;
		if (byte < 0) byte = 0;
		if (byte > 255) byte = 255;

		// write
		output.data[i] = (stbi_uc)byte;
	}

	return output;
}
