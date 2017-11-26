#include <stdlib.h>
#include <stdio.h>
#include "image_loader.h"

int read_number(FILE *input);


unsigned char*
SAIL_load_image(const char *file_path, int *width, int *height) {

	FILE* input;
	fopen_s(&input, file_path, "r");
	if (input == NULL) {
		fprintf(stderr, "Could not open \"%s\"\n", file_path);
		return NULL;
	}
	unsigned char *result = SAIL_load_image_file(input, width, height);
	fclose(input);
	fprintf(stderr, "Image \"%s\" loaded.\n", file_path);
	return result;
}

unsigned char*
SAIL_load_image_file(FILE* input, int *width, int *height) {
	char buffer[2];
	int rbytes = fread(buffer, 2, 1, input);
	if (rbytes != 1 || buffer[0] != 'P' || buffer[1] != '6') {
		fprintf(stderr, "Image type MUST be 'P6'\n");
		return NULL;
	}
	int t_width, t_height, t_max_value = 0;
	t_width = read_number(input);
	t_height = read_number(input);
	t_max_value = read_number(input);
	if (t_max_value > 255) {
		fprintf(stderr, "Cannot process images with bytes bigger than 1 byte.\n");
		return NULL;
	}
	int num_pixels = t_width * t_height * 3;
	unsigned char *result = (unsigned char*)malloc(sizeof(char) * num_pixels);
	if (result == NULL) {
		fprintf(stderr, "Could not allocate %u bytes of memory.\n", num_pixels);
	}
	rbytes = fread(result, num_pixels, 1, input);
	if (rbytes == 0) {
		free(result);
		return NULL;
	}
	*width = t_width;
	*height = t_height;
	return result;
}

int read_number(FILE *input) {
	int number = 0;
	char c = '\0';
	bool begin = false;
	while (fread(&c, 1, 1, input)) {
		if (c >= '0' && c <= '9') {
			if (!begin) {
				begin = true;
				number = c - '0';
			}
			else {
				number = (number * 10) + (c - '0');
			}
		}
		else if (begin) {
			break;
		}
	}
	return number;
}
