
#include "selection_sort.h"


void init_selection_sorter(SelectionSorter* sorter, int* values, ssize_t num_values)
{
    sorter->values = values;
    sorter->num_values = num_values;
    sorter->current_index = 0;
    sorter->current_compared_index = 0;
    sorter->current_min_index = 0;
}


bool selection_sort_step(SelectionSorter* sorter)
{
    int current_min = sorter->values[sorter->current_min_index];
    int current_value = sorter->values[sorter->current_index];

    if (sorter->current_compared_index >= sorter->num_values)
    {
        sorter->values[sorter->current_index] = current_min;
        sorter->values[sorter->current_min_index] = current_value;
        sorter->current_index += 1;
        sorter->current_compared_index = sorter->current_index;
        sorter->current_min_index = sorter->current_index;
    }
    else
    {
        int current_compared_value = sorter->values[sorter->current_compared_index];
        if (current_compared_value < current_min)
        {
            sorter->current_min_index = sorter->current_compared_index;
        }
        sorter->current_compared_index += 1;
    }

    return sorter->current_index == sorter->num_values - 1;
}
