#pragma once

#include "Window.h"
#include "Input.h"
#include "Shader.h"
#include "Buffer.h"
#include "Camera.h"
#include "Callback.h"
#include "Cube.h"

#include <glm/gtc/matrix_transform.hpp>

class Game
{
public:
  Game();

  GLFWwindow* getWindow() const { return m_window; }

  void initialize();
  void processInput();
  void clear();
  void update();
  void render();
  void run();

  Camera& getCamera() { return m_camera; }

private:
  Window m_window{ "LearnOpenGL" };

  Camera m_camera{ 120.f };
};

extern Game game;

