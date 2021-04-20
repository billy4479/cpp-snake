#pragma once

#include <iostream>

#include "Cell.hpp"
#include "Types.hpp"
#include <tuple>
#include <vector>

class Grid {
  public:
    Grid(uint width, uint height);
    ~Grid();

    const Cell GetCellAt(uint x, uint y) const;
    const Cell GetCellAt(std::pair<uint, uint> pos) const;
    void SetCellContentAt(uint x, uint y, Cell newCell);
    void SetCellContentAt(std::pair<uint, uint> position, Cell newCell);

    const uint GetWidth() const;
    const uint GetHeight() const;

  private:
    uint m_width;
    uint m_height;
    std::vector<Cell> m_Grid;

    Cell *GetCellAtMut(uint x, uint y);
};