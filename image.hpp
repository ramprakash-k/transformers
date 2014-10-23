#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "gl_framework.hpp"

struct Image {
	uint32_t sizeX;
	uint32_t sizeY;
    char *data;
};
typedef struct Image Image;

void LoadGLTextures(char *filename,GLuint *texture);

#endif // IMAGE_HPP
