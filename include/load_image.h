#ifndef __LOAD_IMAGE__
#define __LOAD_IMAGE__

typedef struct  s_image
{
    int             width;
    int             height;
    int             channels;
    unsigned char   *pixels;
}               t_image;

int     loadImage(char *path, t_image *img);

#endif