
#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stdbool.h>
#include <sys/types.h>


typedef struct
{
    int* values;
    ssize_t num_values;
    ssize_t current_index;
    ssize_t current_compared_index;
    int current_value;
} InsertionSorter;

void init_insertion_sorter(InsertionSorter* sorter, int* values, ssize_t num_values);
bool insertion_sort_step(InsertionSorter* sorter);


#endif
