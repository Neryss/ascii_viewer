#include <stdio.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/load_image.h"

int loadImage(char *path, t_image *img)
{
    img->pixels = stbi_load(path, &img->width, &img->height, &img->channels, 0);
    if (!img->pixels)
    {
        printf("Error while loading the image\n");
        return (1);
    }
    printf("Loaded image: width %dpx, height %dpx, channels %d\n", img->width, img->height, img->channels);
    return (0);
}
