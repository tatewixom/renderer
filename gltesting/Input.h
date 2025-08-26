#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <unordered_map>

namespace Input
{
  //Checks if the key is currently being pressed and will allow for repeat of input
  bool isKeyPressed(GLFWwindow* window, int key);

  //Checks if the key was just released, doesn't allow for repeat input
  bool isKeyJustPressed(GLFWwindow* window, int key);

  void processWindowEscape(GLFWwindow* window);
}

