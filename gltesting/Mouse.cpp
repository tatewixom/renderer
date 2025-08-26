#include "Mouse.h"
#include "Window.h"
#include "Callback.h"

Mouse mmouse{};

void Mouse::center(Window& window)
{
  glfwSetCursorPos(window, window.width() / 2, window.height() / 2);
}

void Mouse::viewMode(Window& window)
{
  m_position = m_lastPosition;

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Mouse::selectionMode(Window& window)
{
  m_lastPosition = m_position;

  center(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Mouse::isButtonPressed(int mouseButton) const
{
  if (m_button.button == mouseButton && m_button.action == GLFW_PRESS)
    return true;

  return false;
}

bool Mouse::isDisabled(Window& window) const
{
  return glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void Mouse::setLastPosition()
{
  m_position = m_lastPosition;
}

bool operator==(const Mouse::Position& pos1, const Mouse::Position & pos2)
{
  return (pos1.x == pos2.x) && (pos1.y == pos2.y);
}
