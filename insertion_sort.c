
#include "insertion_sort.h"


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
