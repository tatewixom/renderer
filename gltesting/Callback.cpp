#include "Callback.h"
#include "Game.h"

namespace Callback
{
  bool firstMouse{ true };

  double lastX{ (game.getWindow().width()) / 2.0f };
  double lastY{ (game.getWindow().height()) / 2.0f };

  Mouse::Position cameraMovement{};

  void framebuffer(GLFWwindow* window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }

  void mouse(GLFWwindow* window, double xposIn, double yposIn)
  {
    game.getMouse().getPosition().x = xposIn;
    game.getMouse().getPosition().y = yposIn;

    if (firstMouse)
    {
      lastX = xposIn;
      lastY = yposIn;
      firstMouse = false;
    }

    game.getMouse().getLastPosition().x = lastX;
    game.getMouse().getLastPosition().y = lastY;

    //std::cout << mmouse.getLastPosition().x << ' ' << mmouse.getLastPosition().y << '\n';

    game.getMouse().getOffset().x = xposIn - lastX;
    game.getMouse().getOffset().y = lastY - yposIn;

    lastX = xposIn;
    lastY = yposIn;

    const float sensitivity{ 0.1f };

    cameraMovement = Mouse::Position{ game.getMouse().getOffset().x, game.getMouse().getOffset().y };

    cameraMovement.x *= sensitivity;
    cameraMovement.y *= sensitivity;

    if (game.getMouse().isDisabled())
    {
      game.getCamera().yaw += static_cast<float>(cameraMovement.x);
      game.getCamera().pitch += static_cast<float>(cameraMovement.y);

      if (game.getCamera().pitch > 89.0f)
        game.getCamera().pitch = 89.0f;
      if (game.getCamera().pitch < -89.0f)
        game.getCamera().pitch = -89.0f;

      //calculating camera vector
      glm::vec3 direction{};
      direction.x = cos(glm::radians(game.getCamera().yaw)) * cos(glm::radians(game.getCamera().pitch));
      direction.y = sin(glm::radians(game.getCamera().pitch));
      direction.z = sin(glm::radians(game.getCamera().yaw)) * cos(glm::radians(game.getCamera().pitch));
      game.getCamera().front = glm::normalize(direction);
    }
  }

  void scroll(GLFWwindow* window, double xoffset, double yoffset)
  {
    game.getCamera().fov -= static_cast<float>(yoffset);
    if (game.getCamera().fov < 1.0f)
      game.getCamera().fov = 1.0f;
    if (game.getCamera().fov > 120.0f)
      game.getCamera().fov = 120.0f;
  }

  void refresh(GLFWwindow* window)
  {
    //nothing
  }
  void mouseButton(GLFWwindow* window, int button, int action, int mods)
  {
    game.getMouse().getButton().button = button;
    game.getMouse().getButton().action = action;
  }
}