#pragma once

#include "State.h"
#include "Window.h"
#include "Camera.h"
#include "Mouse.h"

class Game
{
public:
  Game();

  void initialize();
  void run();

  Window& getWindow() { return m_window; }
  Mouse& getMouse() { return m_mouse; }
  Camera& getCamera() { return m_camera; }

private:
  Window m_window{ "LearnOpenGL" };
  Mouse m_mouse{ m_window };
  Camera m_camera{ 120.f };
  State m_state{};
};

extern Game game;

