# cpp-snake
A remake of the first project of mine, using Ncurses.

## Building

AFAIK Ncurses is *nix only. To build on linux run:

```bash 
cmake -S . -B build
cmake --build build
```

A modern C++ compiler (c++17), CMake and ncurses are neaded.

On Arch you can intall `base-devel cmake ncurses`, on Ubuntu install `build-essential cmake libncurses5-dev`.
