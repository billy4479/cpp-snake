#pragma once

#include "Cell.hpp"
// #include <exception>
#include <iostream>
#include <memory>
#include <tuple>

class Grid {
  public:
    Grid(uint width, uint height);
    ~Grid();

    Cell GetCellAt(uint x, uint y) const;
    void SetCellContentAt(uint x, uint y, Cell newCell);
    void SetCellContentAt(std::tuple<uint, uint> position, Cell newCell);

    uint GetWidth() const;
    uint GetHeight() const;

  private:
    uint m_width;
    uint m_height;
    std::unique_ptr<Cell[]> m_Grid;

    Cell *GetCellAtMut(uint x, uint y);
};