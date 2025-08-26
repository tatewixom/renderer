#include "Input.h"

bool Input::isKeyPressed(GLFWwindow* window, int key)
{
  return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::isKeyJustPressed(GLFWwindow* window, int key)
{
  //stores previous key state
  static std::unordered_map<int, bool> keyStates;
  bool currentlyPressed = isKeyPressed(window, key);

  //if key was released before and is now pressed
  if (currentlyPressed && !keyStates[key])
  {
    keyStates[key] = true;
    return true;
  }

  if (!currentlyPressed)
  {
    keyStates[key] = false;
  }

  return false;
}

void Input::processWindowEscape(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}