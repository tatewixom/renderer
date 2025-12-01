#pragma once

#include "State.h"
#include "Window.h"
#include "Camera.h"
#include "Mouse.h"

class Game
{
public:
  static Game& getInstance()
  {
    static Game game{};
    return game;
  }

  void initialize();
  void run();

  Window& getWindow() { return m_window; }
  Mouse& getMouse() { return m_mouse; }
  Camera& getCamera() { return m_camera; }

private:
  Game();

  Window m_window{ "LearnOpenGL" };
  Mouse m_mouse{ m_window };
  Camera m_camera{ 120.f };
  State m_state{};
};

