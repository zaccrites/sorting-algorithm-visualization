
#include "bubble_sort.h"


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
