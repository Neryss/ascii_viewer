#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include "../include/load_image.h"

const char  palette[] = "#@+=-:. ";

#define MIN(a,b) (((a)<(b))?(a):(b))

struct winsize  getTermInfo()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    return(w);
}

void    clearScreen()
{
    const char *CLEAR_SCREEN_ANSI = "\x1b[2J";
    write(0, CLEAR_SCREEN_ANSI, 5);
}

int ft_strlen(const char *str)
{
    const char  *s;

    s = str;
    while (*s)
        s++;
    return (s - str);
}

int writeNewLine(char *str)
{
    write(0, str, ft_strlen(str));
    // write(0, "\n", 1);
}


typedef struct engine
{
    char    *buffer;
    int     width;
    int     height;
}           t_engine;

void    clearRender(t_engine *engine)
{
    // for (int i = 0; i < engine->width * engine->height; i++)
    //     engine->buffer[i] = palette[i%7];
    
}

void    render(t_engine *engine)
{
    write(0, engine->buffer, engine->width * engine->height + 1);
    usleep(16000);
    write(0, "\033[35A\033[H", 9);
    clearRender(engine);
}

int initEngine(t_engine *engine, struct winsize w)
{
    engine->buffer = malloc(w.ws_col * w.ws_row * sizeof(char));
    if (!engine->buffer)
        return (1);
    for (int i = 0; i < w.ws_col * w.ws_row; i++)
    {
        // if (i%w.ws_col == 0)
        //     engine->buffer[i] = 'X';
        // else
        engine->buffer[i] = '.';
    }
    engine->buffer[w.ws_col * w.ws_row] = 0;
    engine->width = w.ws_col;
    engine->height = w.ws_row;
    return (0);
}

void    freeEngine(t_engine *engine)
{
    if (engine->buffer)
        free(engine->buffer);
    engine->buffer = NULL;
}

void    putPixel(__uint32_t x, __uint32_t y, t_engine *engine)
{
    if (x >= engine->width || y >= engine->height)
        return;
    engine->buffer[y * engine->width + x] = palette[0];
}

void    drawLine(__uint32_t x, __uint32_t y, __uint32_t width, __uint32_t height, t_engine *engine)
{
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            putPixel(x + i, y + j, engine);
}

int main(int argc, char **argv)
{
    t_image     img;
    loadImage("nazuna_resized.png", &img);
    // unsigned char   *conv = NULL;
    // conv = calloc(img.width * img.height, sizeof(unsigned char));
    // if (!conv)
    //     return (1);
    for (int i = 0; i < img.width * img.height * img.channels; i+=img.channels)
    {
        unsigned char r = img.pixels[i];
        unsigned char g = img.pixels[i+1];
        unsigned char b = img.pixels[i+2];
        unsigned char a = img.channels >= 4 ? img.pixels[i+3] : 0xff;
        int y = 0.299 * r + 0.587 * g + 0.114 * b;
        // printf("[%d, %d, %d, %d]", r, g, b, a);
        int tmp = MIN((y * 8 / 255), 8 - 1);
        printf("%c", palette[tmp]);
        if (i % (img.width * img.channels) == 0)
            printf("\n");
    }
    // struct winsize  w = getTermInfo();
    // printf("lines: %d\n", w.ws_row);
    // printf("cols : %d\n", w.ws_col);
    // // return(0);
    // if (initEngine(&engine, w))
    //     return (1);
    // (void)argc;
    // (void)argv;
    // for(; ;)
    // {
    //     drawLine(0, 0, 10, 10, &engine);
    //     render(&engine);
    // }
    // freeEngine(&engine);
    // return(0);
}