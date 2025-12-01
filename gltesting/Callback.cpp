#include "Callback.h"
#include "Game.h"

namespace Callback
{
  bool firstMouse{ true };

  void framebuffer(GLFWwindow* window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }

  void mouse(GLFWwindow* window, double xposIn, double yposIn)
  {
    Mouse& mouse{ Game::getInstance().getMouse() };

    Mouse::Position currentPos{ xposIn, yposIn };
    mouse.setPosition(currentPos);
  }

  void scroll(GLFWwindow* window, double xoffset, double yoffset)
  {
    float& camerafov{ Game::getInstance().getCamera().fov };

    camerafov -= static_cast<float>(yoffset);
    if (camerafov < 1.0f)
      camerafov = 1.0f;
    if (camerafov > 120.0f)
      camerafov = 120.0f;
  }

  void refresh(GLFWwindow* window)
  {
    //nothing
  }
  void mouseButton(GLFWwindow* window, int button, int action, int mods)
  {
    Mouse::Button& mousebutton{ Game::getInstance().getMouse().getButton() };

    mousebutton.button = button;
    mousebutton.action = action;
  }
}