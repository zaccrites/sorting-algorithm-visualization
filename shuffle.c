
#include <stdlib.h>
#include "shuffle.h"


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
