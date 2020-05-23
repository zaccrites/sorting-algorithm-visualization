
# TODO: Replace with CMake

main: main.c
	gcc -std=c11 -pedantic -Wall -Wextra -O2 main.c -o /tmp/main -lSDL2
