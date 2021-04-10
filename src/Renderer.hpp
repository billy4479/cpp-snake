#pragma once

#include "Grid.hpp"
#include <curses.h>

class Renderer {
  public:
    Renderer(Grid *grid);

    void PrintToStdOut();
    void PrintToNCurses();

  private:
    Grid *m_Grid;
};