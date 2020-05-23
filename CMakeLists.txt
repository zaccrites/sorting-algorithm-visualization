
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(sorting_algorithm_visualization VERSION 0.1.0 LANGUAGES C)


find_package(SDL2 REQUIRED)

add_executable(main
    main.c
)

target_compile_options(main PRIVATE
    -std=c11
    -pedantic
    -Wall
    -Wextra
    -O2
)

target_link_libraries(main
    ${SDL2_LIBRARIES}
)
