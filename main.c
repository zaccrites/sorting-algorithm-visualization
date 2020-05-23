
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "shuffle.h"
#include "selection_sort.h"
#include "insertion_sort.h"
#include "bubble_sort.h"


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600


static int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    else if (arg1 > arg2) return 1;
    else return 0;
}

void sort_int_array(int* values, ssize_t length)
{
    qsort(values, length, sizeof(*values), compare_ints);
}


















int main()
{
    SDL_Window* pWindow = SDL_CreateWindow(
        "Sorting",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (pWindow == NULL)
    {
        fprintf(stderr, "ERROR: Failed to create SDL window \n");
        return 1;
    }

    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (pRenderer == NULL)
    {
        fprintf(stderr, "ERROR: Failed to create SDL renderer \n");
        return 1;
    }


    srand(time(NULL));

    #define NUM_VALUES  512
    int values[NUM_VALUES];
    for (ssize_t i = 0; i < NUM_VALUES; i++)
    {
        // values[i] = 1 + rand() % 499;
        values[i] = i;
    }
    shuffle(values, NUM_VALUES);

    // To verify sorting algorithms work
    // sort_int_array(values, NUM_VALUES);

    // BubbleSorter sorter;
    // init_bubble_sorter(&sorter, values, NUM_VALUES);
    // while ( ! bubble_sort_step(&sorter));

    // InsertionSorter sorter;
    // init_insertion_sorter(&sorter, values, NUM_VALUES);

    SelectionSorter sorter;
    init_selection_sorter(&sorter, values, NUM_VALUES);

    // TODO
    bool arraySorted = false;
    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            isRunning = false;
                            break;
                    }
            }
        }


        SDL_SetRenderDrawColor(pRenderer, 0x64, 0x95, 0xed, 0xff);
        SDL_RenderClear(pRenderer);

        for (ssize_t i = 0; i < NUM_VALUES; i++)
        {
            if (arraySorted)
            {
                SDL_SetRenderDrawColor(pRenderer, 0x00, 0xff, 0x00, 0xff);
            }
            else if (i == sorter.current_index)
            {
                SDL_SetRenderDrawColor(pRenderer, 0xff, 0x00, 0x00, 0xff);
            }
            else if (i == sorter.current_compared_index)
            {
                SDL_SetRenderDrawColor(pRenderer, 0x00, 0xff, 0x00, 0xff);
            }
            else
            {
                SDL_SetRenderDrawColor(pRenderer, 0xff, 0xff, 0xff, 0xff);
            }

            // TODO: Just update a streaming texture and RenderCopy that
            // instead. It's almost certainly faster than drawing hundreds
            // of filled rectangles.
            SDL_Rect rect = {
                .x = 64 + 1 * i,
                .y = WINDOW_HEIGHT - 64 - values[i],
                .w = 1,
                .h = values[i],
            };
            SDL_RenderFillRect(pRenderer, &rect);
        }


        SDL_RenderPresent(pRenderer);

        // SDL_Delay(4);
        // SDL_Delay(2);

        if ( ! arraySorted)
        {
            // arraySorted = bubble_sort_step(&sorter);
            // arraySorted = insertion_sort_step(&sorter);
            arraySorted = selection_sort_step(&sorter);
        }

    }

    if (pRenderer)
    {
        SDL_DestroyRenderer(pRenderer);
    }

    if (pWindow)
    {
        SDL_DestroyWindow(pWindow);
    }

    SDL_Quit();
}
