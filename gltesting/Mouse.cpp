#include "Mouse.h"
#include "Window.h"
#include "Callback.h"

Mouse::Mouse(Window& window)
  : m_window{ window }
{
  glfwSetCursorPosCallback(m_window, Callback::mouse);
  glfwSetScrollCallback(m_window, Callback::scroll);
  glfwSetMouseButtonCallback(m_window, Callback::mouseButton);
}

void Mouse::update()
{
  static bool firstMouse{ true };

  if (firstMouse) 
  {
    center();
    m_position = Mouse::Position{ m_window.width() / 2.0f, m_window.height() / 2.0f }; //preventing mouse "snapping" into position
    m_lastPosition = m_position;
    firstMouse = false;
  }

  m_offset.x = m_position.x - m_lastPosition.x; //calculating offset
  m_offset.y = m_lastPosition.y - m_position.y;

  m_lastPosition = m_position; //setting last position
}

void Mouse::center()
{
  glfwSetCursorPos(m_window, m_window.width() / 2, m_window.height() / 2);
}

void Mouse::viewMode()
{
  m_position = m_lastPosition;

  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Mouse::selectionMode()
{
  m_lastPosition = m_position;

  center();
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Mouse::isButtonPressed(int mouseButton) const
{
  if (m_button.button == mouseButton && m_button.action == GLFW_PRESS)
    return true;

  return false;
}

bool Mouse::isDisabled() const
{
  return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void Mouse::setLastPosition()
{
  m_position = m_lastPosition;
}

bool operator==(const Mouse::Position& pos1, const Mouse::Position & pos2)
{
  return (pos1.x == pos2.x) && (pos1.y == pos2.y);
}

Mouse::Position operator-(const Mouse::Position& pos1, const Mouse::Position& pos2)
{
  return Mouse::Position{ pos1.x - pos2.x, pos1.y - pos2.y };
}
