#define NOB_WARN_DEPRECATED
#define NOB_UNSTRIP_PREFIXES
#define NOB_IMPLEMENTATION
#include "include/nob.h"

#define TARGET "lumina"
#define OBJ_DIR "build/"
#define HDR_DIR "include/"
#define SRC_DIR "src/"

#define CFLAGS "-std=c23",   \
	       "-g",         \
	       "-Wall",      \
	       "-Wextra",    \
	       "-Wpedantic", \
	       "-D_POSIX_C_SOURCE=200809L"

#define LDFLAGS "-lraylib",  \
	        "-lm",       \
	        "-lpthread", \
	        "-ldl",      \
	        "-lrt",      \
	        "-lX11",     \
	        "-lGL"

static struct {
	const char* hdr;
	const char* src;
	const char* obj;
} translation_units[] = {
	{ .hdr = HDR_DIR "nob.h",             .src = SRC_DIR "nob.c",             .obj = OBJ_DIR "nob.o"             },
	{ .hdr = HDR_DIR "main.h",            .src = SRC_DIR "main.c",            .obj = OBJ_DIR "main.o"            },
	{ .hdr = HDR_DIR "utils.h",           .src = SRC_DIR "utils.c",           .obj = OBJ_DIR "utils.o"           },
	{ .hdr = HDR_DIR "lumina.h",          .src = SRC_DIR "lumina.c",          .obj = OBJ_DIR "lumina.o"          },
	{ .hdr = HDR_DIR "stb_image.h",       .src = SRC_DIR "stb_image.c",       .obj = OBJ_DIR "stb_image.o"       },
	{ .hdr = HDR_DIR "stb_image_write.h", .src = SRC_DIR "stb_image_write.c", .obj = OBJ_DIR "stb_image_write.o" },
};

int main(int argc, char* argv[argc])
{
	NOB_GO_REBUILD_URSELF(argc, argv);

	if (!nob_mkdir_if_not_exists(OBJ_DIR)) {
		return 1;
	}

	Nob_Cmd cmd     = { 0 };
	Nob_Procs procs = { 0 };

	for (size_t i = 0; i < NOB_ARRAY_LEN(translation_units); ++i) {
		cmd.count = 0;
		nob_cmd_append(&cmd, "cc", CFLAGS);
		nob_cmd_append(&cmd, "-I", HDR_DIR, "-o", translation_units[i].obj, "-c", translation_units[i].src);
		if (!nob_cmd_run(&cmd, .async = &procs)) {
			return 1;
		}
	}

	if (!procs_flush(&procs)) {
		return 1;
	}

	cmd.count = 0;
	nob_cmd_append(&cmd, "cc", "-o", TARGET);
	for (size_t i = 0; i < NOB_ARRAY_LEN(translation_units); ++i) {
		nob_cmd_append(&cmd, translation_units[i].obj);
	}

	nob_cmd_append(&cmd, LDFLAGS);
	if (!nob_cmd_run(&cmd)) {
		return 1;
	}

#ifndef LUMINA_NO_REPORT
	cmd.count = 0;
	nob_cmd_append(&cmd, "latex");
	nob_cmd_append(&cmd, "-shell-escape");
	nob_cmd_append(&cmd, "-halt-on-error");
	nob_cmd_append(&cmd, "-output-format=pdf");
	nob_cmd_append(&cmd, "report.tex");

	if (!nob_cmd_run(&cmd)) {
		return 1;
	}
#endif // LUMINA_NO_REPORT

	return 0;
}
