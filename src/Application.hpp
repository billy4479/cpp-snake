#pragma once

#include "Grid.hpp"
#include "Renderer.hpp"
#include "Snake.hpp"
#include <chrono>
#include <curses.h>
#include <string>
#include <thread>

class Application {
  public:
    Application();
    ~Application();
    void Run();

  private:
    Grid *m_Grid;
    Renderer *m_Renderer;
    WINDOW *m_Window;
    Snake *m_Snake;

    bool running = true;

    void Frame();
    void HandleInputs();
};