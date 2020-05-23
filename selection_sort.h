
#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <stdbool.h>
#include <sys/types.h>


typedef struct
{
    int* values;
    ssize_t num_values;
    ssize_t current_index;
    ssize_t current_compared_index;
    ssize_t current_min_index;
} SelectionSorter;

void init_selection_sorter(SelectionSorter* sorter, int* values, ssize_t num_values);
bool selection_sort_step(SelectionSorter* sorter);


#endif
