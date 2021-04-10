#include "Application.hpp"
#include "Direction.hpp"
#include <curses.h>

Application::Application() {
    m_Window = initscr();
    int row, col;
    getmaxyx(m_Window, row, col);

    m_Grid = new Grid(col - 1, row - 1);
    m_Renderer = new Renderer(m_Grid);

    m_Snake = new Snake(m_Grid->GetWidth() / 2, m_Grid->GetHeight() / 2);

    noecho();
    cbreak();
    nodelay(m_Window, true);
}

Application::~Application() {
    endwin();
    delete m_Renderer;
    delete m_Grid;
    delete m_Snake;
}

void Application::HandleInputs() {
    auto key = getch();

    while (key != -1) {
        switch (key) {
        case '\033':
            // See:
            // https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
            // and
            // https://stackoverflow.com/questions/5977395/ncurses-and-esc-alt-keys

            key = getch();
            if (key == -1) {
                running = false;
                key = -1;
                break;
            }

            key = getch();
            switch (key) { // the real value
            case 'A':
                // code for arrow up
                if (m_Snake->GetDirection() != Direction::DOWN)
                    m_Snake->SetDirection(Direction::UP);
                break;
            case 'B':
                // code for arrow down
                if (m_Snake->GetDirection() != Direction::UP)
                    m_Snake->SetDirection(Direction::DOWN);
                break;
            case 'C':
                // code for arrow right
                if (m_Snake->GetDirection() != Direction::LEFT)
                    m_Snake->SetDirection(Direction::RIGHT);
                break;
            case 'D':
                // code for arrow left
                if (m_Snake->GetDirection() != Direction::RIGHT)
                    m_Snake->SetDirection(Direction::LEFT);
                break;
            }
            break;
        case 'q':
        case KEY_EXIT:
            running = false;
            key = -1;
            break;

        default:
            key = -1;
            break;
        }
    }
}

void Application::Frame() {
    HandleInputs();

    auto pos = m_Snake->GetPosition();

    m_Snake->UpdatePosition();
    m_Grid->SetCellContentAt(pos, Cell::HEAD);

    m_Renderer->PrintToNCurses();

    int i = 0;
    for (auto p : m_Snake->GetOldPositions()) {

        if (i >= m_Snake->length) {
            m_Grid->SetCellContentAt(p, Cell::EMPTY);
        }
        m_Grid->SetCellContentAt(p, Cell::TAIL);

        i++;
    }
}

void Application::Run() {
    const auto frametime = std::chrono::milliseconds(100);

    while (running) {
        Frame();
        std::this_thread::sleep_for(frametime);
    }
}
