#include "Snake.hpp"

Snake::Snake(uint initialX, uint initialY)
    : x(initialX), y(initialY), m_Direction(Direction::RIGHT) {}

const std::vector<std::pair<uint, uint>> *Snake::GetOldPositions() const {
    return &m_OldPositions;
}

std::pair<uint, uint> Snake::GetPosition() const { return std::pair(x, y); }

void Snake::SetDirection(Direction direction) { m_Direction = direction; }
Direction Snake::GetDirection() const { return m_Direction; }

void Snake::UpdatePosition() {
    m_OldPositions.push_back(std::pair(x, y));
    switch (m_Direction) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case RIGHT:
        x++;
        break;
    case LEFT:
        x--;
        break;
    }
}