
# Sorting Algorithm Visualization

Uses SDL to render sorting algorithms step-by-step.

The following algorithms are implemented:

* [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort)
* [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort)
* [Selection sort](https://en.wikipedia.org/wiki/Selection_sort)
* **TODO**: [Quicksort](https://en.wikipedia.org/wiki/Quicksort)
* **TODO**: [Merge sort](https://en.wikipedia.org/wiki/Merge_sort)

All sorting is done in-place.
The implementations are structured in such a way that a single step
of the algorithm can be performed in a single function call,
which makes it suitable for visualization by displaying the state of the
array at each step before it is completely sorted.


## Development

    $ apt install libsdl2-dev
    $ make && /tmp/main
