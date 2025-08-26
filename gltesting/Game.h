#pragma once

#include "State.h"
#include "Window.h"
#include "Camera.h"

class Game
{
public:
  Game();

  GLFWwindow* getWindow() const { return m_window; }

  void initialize();
  void run();

  Camera& getCamera() { return m_camera; }
  Window& getWindow() { return m_window; }

private:
  State m_state{};

  Window m_window{ "LearnOpenGL" };
  Camera m_camera{ 120.f };
};

extern Game game;

