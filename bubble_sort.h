
#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <stdbool.h>
#include <sys/types.h>


typedef struct
{
    int* values;
    ssize_t num_values;
    ssize_t num_values_placed;
    ssize_t current_index;
    ssize_t current_compared_index;
    bool any_swaps_this_pass;
} BubbleSorter;

void init_bubble_sorter(BubbleSorter* sorter, int* values, ssize_t num_values);
bool bubble_sort_step(BubbleSorter* sorter);


#endif
