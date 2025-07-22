#pragma once

#include "Game.h"

namespace Callback
{
  void framebuffer(GLFWwindow* window, int width, int height);
  void mouse(GLFWwindow* window, double xposIn, double yposIn);
  void scroll(GLFWwindow* window, double xoffset, double yoffset);
  void refresh(GLFWwindow* window);
}