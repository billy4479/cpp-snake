#pragma once

#include "Grid.hpp"
#include "Snake.hpp"
#include <chrono>
#include <curses.h>
#include <random>
#include <thread>
#include <tuple>

class Application {
  public:
    Application();
    ~Application();
    void Run();

  private:
    Grid *m_Grid;
    Snake *m_Snake;
    std::default_random_engine m_Generator;
    std::uniform_int_distribution<uint> m_HorizontalDistribution;
    std::uniform_int_distribution<uint> m_VerticalDistribution;

    bool running = true;

    uint fruitX = 0;
    uint fruitY = 0;

    void Frame();
    void HandleInputs();
    void RenderGrid();
    void PlaceFruit();

    std::pair<uint, uint> InitWindow();
    void EndWindow();
};