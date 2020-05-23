
// #include <stdio.h>
// #include <stddef.h>




// static void merge_sort_range(int* values, ssize_t start, ssize_t end)
// {
//     printf("start = %d, end = %d \n", start, end);
//     if (end - start < 2)
//     {

//     }
//     else
//     {
//         ssize_t middle = (start + end) / 2;
//         merge_sort_range(values, start, middle);
//         merge_sort_range(values, middle, end);
//     }
// }


// void merge_sort(int* values, ssize_t length)
// {
//     merge_sort_range(values, 0, length);
// }


// int main()
// {
//     int values[] = {3, 40, -1, 5, 10, 100, 201, 0, 3};
//     ssize_t numValues = sizeof(values) / sizeof(values[0]);
//     merge_sort(values, numValues);

//     return 0;
// }


#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include <stdio.h>
#include <SDL2/SDL.h>


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




typedef struct
{
    int* values;
    ssize_t num_values;
    ssize_t num_values_placed;
    ssize_t current_index;
    ssize_t current_compared_index;
    bool any_swaps_this_pass;
} BubbleSorter;

void init_bubble_sorter(BubbleSorter* sorter, int* values, ssize_t num_values)
{
    sorter->values = values;
    sorter->num_values = num_values;
    sorter->num_values_placed = 0;
    sorter->current_index = 0;
    sorter->current_compared_index = 0;
    sorter->any_swaps_this_pass = false;
}

bool bubble_sort_step(BubbleSorter* sorter)
{
    sorter->current_compared_index = sorter->current_index + 1;

    int a = sorter->values[sorter->current_index];
    int b = sorter->values[sorter->current_compared_index];
    bool do_swap = b < a;
    if (do_swap)
    {
        sorter->values[sorter->current_index] = b;
        sorter->values[sorter->current_compared_index] = a;
        sorter->any_swaps_this_pass = true;
    }

    sorter->current_index = sorter->current_compared_index;
    if (sorter->current_index >= sorter->num_values - sorter->num_values_placed - 1)
    {
        // A swap at the end means that we don't have to check that
        // value again.
        if (do_swap)
        {
            sorter->num_values_placed += 1;
            // printf("%d values placed \n", sorter->num_values_placed);
        }

        // If we're at the end and there were no swaps then we know
        // the sort is finished.
        if ( ! sorter->any_swaps_this_pass)
        {
            return true;
        }

        sorter->current_index = 0;
        sorter->any_swaps_this_pass = false;
    }

    return false;
}



typedef struct
{
    int* values;
    ssize_t num_values;
    ssize_t current_index;
    ssize_t current_compared_index;
    int current_value;
} InsertionSorter;

void init_insertion_sorter(InsertionSorter* sorter, int* values, ssize_t num_values)
{
    sorter->values = values;
    sorter->num_values = num_values;
    sorter->current_index = 1;
    sorter->current_compared_index = 0;
    sorter->current_value = sorter->values[sorter->current_index];
}

bool insertion_sort_step(InsertionSorter* sorter)
{
    int compared_value = sorter->values[sorter->current_compared_index];
    if (compared_value <= sorter->current_value || sorter->current_compared_index < 0)
    {
        sorter->values[sorter->current_compared_index + 1] = sorter->current_value;

        // Move on to the next element.
        sorter->current_index += 1;
        sorter->current_compared_index = sorter->current_index - 1;
        sorter->current_value = sorter->values[sorter->current_index];

        if (sorter->current_index == sorter->num_values)
        {
            return true;
        }
    }
    else
    {
        // Shift sorted elements over to make room for the current value
        // we're inserting.
        sorter->values[sorter->current_compared_index + 1] = compared_value;
        sorter->current_compared_index -= 1;
    }
    return false;
}



// Fisher-Yates shuffle
void shuffle(int* values, ssize_t num_values)
{
    for (ssize_t i = num_values - 1; i != 0; i--)
    {
        ssize_t j = rand() % i;
        int tmp = values[j];
        values[j] = values[i];
        values[i] = tmp;
    }
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

    InsertionSorter sorter;
    init_insertion_sorter(&sorter, values, NUM_VALUES);

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
            arraySorted = insertion_sort_step(&sorter);
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
