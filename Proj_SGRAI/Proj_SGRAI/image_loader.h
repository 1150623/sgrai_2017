#pragma once
#ifndef IMAGE_LOADER_HPP_
#define IMAGE_LOADER_HPP_

#include <stdlib.h>
#include <stdio.h>


unsigned char* SAIL_load_image(const char *file_path, int *width, int *height);

unsigned char* SAIL_load_image_file(FILE* input, int *width, int *height);

#endif  // IMAGE_LOADER_HPP_

