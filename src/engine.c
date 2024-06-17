#include "../include/engine.h"

#define WIDTH 80
#define HEIGHT 10

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    int current = 0;
    for (;;)
    {
        printf("\033[H\033[J");
        for (size_t y = 0; y < HEIGHT; ++y)
        {
            for (size_t x = 0; x < WIDTH; ++x)
            {
                if (x % 2)
                    printf("\e[1;34m\u2588\e[m");
                else
                    printf("\u2588");
            }
            printf("%c", '\n');
        }
        printf("\033[%d;%dH", 1, WIDTH);
        sleep(1);
    }
    return(0);
}