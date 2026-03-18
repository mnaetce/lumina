#include <raylib.h>
#include <stdio.h>
#include "nob.h"
#include "utils.h"
#include "lumina.h"

typedef enum {
	TASK_ENHC,
	TASK_BLUR,
	TASK_ARMF,
	TASK_GEMF,
	TASK_GLPF,
	TASK_BLPF,
	TASK_GHPF,
	TASK_BHPF,
	TASK_ADMF,
} LuTask;

void lu_log_help(FILE* stream)
{
	fprintf(stream, "usage: lumina <task> [input_image]\n"
	                "tasks:\n"
	                "    lumina help                display this message\n"
	                "    lumina enhc <image>        enhance the image\n"
	                "    lumina blur <image>        blur the image\n"
	                "    lumina armf <image>        apply Arithmetic Mean Filter to the image\n"
	                "    lumina gemf <image>        apply Geometric Mean Filter to the image\n"
	                "    lumina glpf <image>        apply Gaussian Lowpass Filter to the image\n"
	                "    lumina blpf <image>        apply Butterworth Lowpass Filter to the image\n"
	                "    lumina ghpf <image>        apply Gaussian Highpass Filter to the image\n"
	                "    lumina bhpf <image>        apply Butterworth Highpass Filter to the image\n"
	                "    lumina admf <image>        apply Adaptive Median Filter to the image\n");
}

int main(int argc, char* argv[argc])
{
	const char* program_path = nob_shift(argv, argc);
	NOB_UNUSED(program_path);

	// Checking if user provided task
	if (argc < 1) {
		nob_log(NOB_ERROR, "No task provided");
		lu_log_help(stderr);
		return 1;
	}

	// Parsing task
	const char* task_str = nob_shift(argv, argc);
	nob_log(NOB_INFO, "Task provided: %s", task_str);
	LuTask task;
	if (lu_str_eq(task_str, "help")) {
		lu_log_help(stdout);
		return 0;
	} else if (lu_str_eq(task_str, "enhc")) {
		task = TASK_ENHC;
	} else if (lu_str_eq(task_str, "blur")) {
		task = TASK_BLUR;
	} else if (lu_str_eq(task_str, "armf")) {
		task = TASK_ARMF;
	} else if (lu_str_eq(task_str, "gemf")) {
		task = TASK_GEMF;
	} else if (lu_str_eq(task_str, "glpf")) {
		task = TASK_GLPF;
	} else if (lu_str_eq(task_str, "blpf")) {
		task = TASK_BLPF;
	} else if (lu_str_eq(task_str, "ghpf")) {
		task = TASK_GHPF;
	} else if (lu_str_eq(task_str, "bhpf")) {
		task = TASK_BHPF;
	} else if (lu_str_eq(task_str, "admf")) {
		task = TASK_ADMF;
	} else {
		nob_log(NOB_ERROR, "Unknown task `%s`", task_str);
		lu_log_help(stderr);
		return 1;
	}

	// Checking if user provided input image path
	if (argc < 1) {
		nob_log(NOB_ERROR, "No input image provided");
		lu_log_help(stderr);
		return 1;
	}

	// Loading input image
	const char* input_path = nob_shift(argv, argc);
	nob_log(NOB_INFO, "Input image: %s", input_path);
	LuImage input = lu_image_load(input_path);

	// Performing the task
	LuImage output = { 0 };
	switch (task) {
	case TASK_ENHC: output = lu_enhance(input); break;
	case TASK_BLUR: output = lu_blur(input); break;
	case TASK_ARMF: LU_UNIMPLEMENTED(); break;
	case TASK_GEMF: LU_UNIMPLEMENTED(); break;
	case TASK_GLPF: LU_UNIMPLEMENTED(); break;
	case TASK_BLPF: LU_UNIMPLEMENTED(); break;
	case TASK_GHPF: LU_UNIMPLEMENTED(); break;
	case TASK_BHPF: LU_UNIMPLEMENTED(); break;
	case TASK_ADMF: LU_UNIMPLEMENTED(); break;
	default: NOB_UNREACHABLE("Unreachable task"); break;
	}

	// Writing output image
	lu_image_write(output);

	// Raylib visualization
	Image rl_input  = LoadImage(input.path);
	Image rl_output = LoadImage(output.path);

	int window_width  = rl_input.width + rl_output.width;
	int window_height = LU_MAX(rl_input.height, rl_output.height);

	InitWindow(window_width, window_height, "lumina");
	Texture2D rl_input_texture  = LoadTextureFromImage(rl_input);
	Texture2D rl_output_texture = LoadTextureFromImage(rl_output);

	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(BLACK);
			DrawTexture(rl_input_texture, 0, 0, WHITE);
			DrawTexture(rl_output_texture, rl_input.width, 0, WHITE);
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
