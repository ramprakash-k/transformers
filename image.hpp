#ifndef _IMAGE_TEX_HPP_
#define _IMAGE_TEX_HPP_

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

void LoadGLTextures(char *filename,GLuint *texture);

#endif
