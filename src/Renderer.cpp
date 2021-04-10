#include "Renderer.hpp"
#include "Cell.hpp"

Renderer::Renderer(Grid *grid) : m_Grid(grid) {}

void Renderer::PrintToStdOut() {
    for (unsigned int y = 0; y < m_Grid->GetHeight(); y++) {
        for (unsigned int x = 0; x < m_Grid->GetWidth(); x++) {
            std::cout << m_Grid->GetCellAt(x, y);

            if (x == m_Grid->GetWidth() - 1)
                std::cout << std::endl;
        }
    }
}

void Renderer::PrintToNCurses() {
    clear();

    for (unsigned int y = 0; y < m_Grid->GetHeight(); y++) {
        for (unsigned int x = 0; x < m_Grid->GetWidth(); x++) {
            printw("%c", m_Grid->GetCellAt(x, y));

            if (x == m_Grid->GetWidth() - 1)
                printw("\n");
        }
    }
    refresh();
}