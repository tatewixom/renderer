#include "Callback.h"

namespace Callback
{
  bool firstMouse{ true };
  float lastX{ 1200.0f / 2.0 };
  float lastY{ 1000.0 / 2.0 };

  void framebuffer(GLFWwindow* window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }

  void mouse(GLFWwindow* window, double xposIn, double yposIn)
  {
    if (firstMouse)
    {
      lastX = static_cast<float>(xposIn);
      lastY = static_cast<float>(yposIn);
      firstMouse = false;
    }

    float xOffset{ static_cast<float>(xposIn) - lastX };
    float yOffset{ lastY - static_cast<float>(yposIn) };
    lastX = static_cast<float>(xposIn);
    lastY = static_cast<float>(yposIn);

    const float sensitivity{ 0.1f };
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    game.getCamera().yaw += xOffset;
    game.getCamera().pitch += yOffset;

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
}