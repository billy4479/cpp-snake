#include "Grid.hpp"

Grid::Grid(uint width, uint height) : m_height(height), m_width(width) {
    m_Grid = std::vector<Cell>(m_height * m_width);

    for (uint y = 0; y < m_height; y++) {
        for (uint x = 0; x < m_width; x++) {
            if (y == 0) {
                SetCellContentAt(x, y, Cell::BORDER);
                continue;
            }
            if (y == m_height - 1) {
                SetCellContentAt(x, y, Cell::BORDER);
                continue;
            }
            if (x == 0) {
                SetCellContentAt(x, y, Cell::BORDER);
                continue;
            }
            if (x == m_width - 1) {
                SetCellContentAt(x, y, Cell::BORDER);
                continue;
            }
            SetCellContentAt(x, y, Cell::EMPTY);
        }
    }
}

Grid::~Grid() = default;

const Cell Grid::GetCellAt(uint x, uint y) const {
    if (x >= m_width || y >= m_height) {
        std::cerr << "Error: requested cell (" << x << ", " << y
                  << "). Grid size is " << m_width << "x" << m_height << ".\n";
        throw;
    }
    return m_Grid[y * m_width + x];
}

const Cell Grid::GetCellAt(std::pair<uint, uint> pos) const {
    return GetCellAt(std::get<0>(pos), std::get<1>(pos));
}

Cell *Grid::GetCellAtMut(uint x, uint y) {
    if (x >= m_width || y >= m_height) {
        std::cerr << "Error: requested cell (" << x << ", " << y
                  << "). Grid size is " << m_width << "x" << m_height << ".\n";
        throw;
    }

    return &m_Grid[y * m_width + x];
}

void Grid::SetCellContentAt(uint x, uint y, Cell newCell) {
    auto cell_ptr = GetCellAtMut(x, y);
    *cell_ptr = newCell;
}

void Grid::SetCellContentAt(std::pair<uint, uint> position, Cell newCell) {
    SetCellContentAt(std::get<0>(position), std::get<1>(position), newCell);
}

const uint Grid::GetHeight() const { return m_height; }
const uint Grid::GetWidth() const { return m_width; }
