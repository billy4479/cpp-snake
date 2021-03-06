#include "Application.hpp"
#include "Cell.hpp"
#include <curses.h>

Application::Application() {
    auto size = InitWindow();

    m_Grid = new Grid(std::get<0>(size), std::get<1>(size));
    m_Snake = new Snake(m_Grid->GetWidth() / 2, m_Grid->GetHeight() / 2);

    m_Generator = std::default_random_engine(
        std::chrono::system_clock::now().time_since_epoch().count());
    m_HorizontalDistribution =
        std::uniform_int_distribution<uint>(1, m_Grid->GetWidth() - 1);
    m_VerticalDistribution =
        std::uniform_int_distribution<uint>(1, m_Grid->GetHeight() - 1);
}

Application::~Application() {
    EndWindow();
    delete m_Grid;
    delete m_Snake;
}

void Application::RenderGrid() {
    clear();

    for (uint y = 0; y < m_Grid->GetHeight(); y++) {
        for (uint x = 0; x < m_Grid->GetWidth(); x++) {

#ifdef USE_COLORS
            auto c = m_Grid->GetCellAt(x, y);
            switch (c) {
            case HEAD:
            case TAIL:
                attron(A_BOLD);
                attron(COLOR_PAIR(1));
                printw("%c", c);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
                break;
            case FOOD:
                attron(A_BOLD);
                attron(COLOR_PAIR(2));
                printw("%c", c);
                attroff(COLOR_PAIR(2));
                attroff(A_BOLD);
                break;
            case BORDER:
                attron(A_BOLD);
                attron(COLOR_PAIR(3));
                printw("%c", c);
                attroff(COLOR_PAIR(3));
                attroff(A_BOLD);
                break;
            case EMPTY:
                printw("%c", c);
                break;
            }
#else
            printw("%c", m_Grid->GetCellAt(x, y));
#endif

            // if (x == m_Grid->GetWidth() - 1)
            //     printw("\n");
        }
    }

    printw("Score: %d", m_Snake->length);

    refresh();
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

void Application::PlaceFruit() {
    while (true) {
        auto possibleX = m_HorizontalDistribution(m_Generator);
        auto possibleY = m_VerticalDistribution(m_Generator);

        if (m_Grid->GetCellAt(possibleX, possibleY) != Cell::EMPTY)
            continue;

        m_Grid->SetCellContentAt(possibleX, possibleY, Cell::FOOD);
        return;
    }
}

void Application::Frame() {
    RenderGrid();

    HandleInputs();
    m_Snake->UpdatePosition();

    auto pos = m_Snake->GetPosition();
    auto oldContent = m_Grid->GetCellAt(pos);

    switch (oldContent) {
    case BORDER:
    case TAIL:
        running = false;
        return;
    case FOOD:
        m_Snake->length++;
        PlaceFruit();
        break;
    case EMPTY:
        break;
    default:
        break;
    }

    m_Grid->SetCellContentAt(pos, Cell::HEAD);

    int i = 0;
    for (auto v = m_Snake->GetOldPositions()->crbegin();
         v != m_Snake->GetOldPositions()->crend(); ++v) {

        if (i >= m_Snake->length) {
            m_Grid->SetCellContentAt(*v, Cell::EMPTY);
            break;
        } else
            m_Grid->SetCellContentAt(*v, Cell::TAIL);

        i++;
    }
}

std::pair<uint, uint> Application::InitWindow() {
    auto window = initscr();

#ifdef USE_COLORS
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
#endif

    uint row, col;
    getmaxyx(window, col, row);
    noecho();
    cbreak();
    nodelay(window, true);
    return std::make_pair(row, col - 1);
}
void Application::EndWindow() { endwin(); }

void Application::Run() {

    PlaceFruit();

    while (running) {
        auto startTime = std::chrono::high_resolution_clock::now();

        Frame();
        printw("\tFPS: %f", lastFPS);
        refresh();

        auto renderTime =
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now() - startTime)
                .count();

        if (frameDelay > renderTime)
            std::this_thread::sleep_for(
                std::chrono::microseconds(frameDelay - renderTime));

        auto endTime =
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now() - startTime)
                .count();

        lastFPS = 1.f / ((float)endTime / 1000000.f);
    }
}
