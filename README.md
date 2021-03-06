
# Sorting Algorithm Visualization

Uses SDL to render sorting algorithms step-by-step.

![Selection Sort](screenshots/selection_sort.png "Selection Sort")

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

    $ apt install cmake libsdl2-dev
    $ git clone https://github.com/zaccrites/sorting-algorithm-visualization
    $ cmake -B ~/sorting-build -S sorting-algorithm-visualization
    $ make -C ~/sorting-build
    $ ~/sorting-build/main
