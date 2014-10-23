#include <stdlib.h>
#include <stdio.h>
#include "image.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int ImageLoad(char *filename, Image *image) {
    uint size;
    uint i;
    uint16_t planes;
    uint16_t bpp;
    uint32_t image_start;
    char temp;

    ifstream file(filename, ifstream::binary);
    if (!file)
    {
        printf("File Not Found : %s\n",filename);
        return 0;
    }

    file.seekg(10, ios_base::cur);
    file.read((char *)&image_start, 4);
    cout<<"Image start: "<<image_start<<endl;

    file.seekg(4, ios_base::cur);

    file.read((char *)&image->sizeX, 4);
    printf("Width of %s: %lu\n", filename, image->sizeX);

    file.read((char *)&image->sizeY, 4);
    printf("Height of %s: %lu\n", filename, image->sizeY);

    size = image->sizeX * image->sizeY * 4;

    file.read((char *)&planes, 2);
    if (planes != 1)
    {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }

    file.read((char *)&bpp, 2);
    if (bpp != 32)
    {
        printf("Bpp from %s is not 32: %u\n", filename, bpp);
        return 0;
    }

    file.seekg(image_start+1, ios_base::beg);

    image->data = (char *) malloc(size);
    if (image->data == NULL)
    {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }

    file.read(image->data, size);

    for (i=0;i<size;i+=4)
    {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }

    return 1;
}

void LoadGLTextures(char *filename,GLuint *texture)
{
    Image *image1;

    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
        printf  ("Error allocating space for image");
        exit(1);
    }

    if (!ImageLoad(filename, image1)) {
        printf("Failed to load");
        exit(0);
    }

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image1->sizeX, image1->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1->data);
    free(image1->data);
    free(image1);
};
