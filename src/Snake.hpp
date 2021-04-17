#pragma once

#include "Direction.hpp"
#include "Types.hpp"
#include <tuple>
#include <vector>

class Snake {
  public:
    Snake(uint initialX, uint initialY);
    void UpdatePosition();
    void SetDirection(Direction direction);
    std::pair<uint, uint> GetPosition() const;
    Direction GetDirection() const;
    const std::vector<std::pair<uint, uint>> *GetOldPositions() const;
    uint length = 0;

  private:
    uint x, y;
    Direction m_Direction;
    std::vector<std::pair<uint, uint>> m_OldPositions;
};