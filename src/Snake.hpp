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
    std::tuple<uint, uint> GetPosition() const;
    Direction GetDirection() const;
    std::vector<std::tuple<uint, uint>> GetOldPositions() const;
    uint length = 0;

  private:
    uint x, y;
    Direction m_Direction;
    std::vector<std::tuple<uint, uint>> m_OldPositions;
};