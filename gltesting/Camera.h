#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
  enum Movement
  {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
  };

  Camera(float vfov = 90.0f, glm::vec3 vposition = { 0.0f, 0.0f, 3.0f }, float vspeed = 5.0f, float vsensitivity = 0.1f);

  glm::vec3 position{};
  glm::vec3 front{};
  glm::vec3 up{};
  glm::vec3 direction{};
  glm::vec3 right{};

  static constexpr glm::vec3 worldUp{ 0.0f, 1.0f, 0.0f };
  static constexpr float nearPlane{ 0.01f };
  static constexpr float farPlane{ 100.0f };

  float yaw{ -90.0f };	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
  float pitch{ 0.0f };

  float fov{};
  float speed{};
  float sensitivity{};
  float zoom{};

  void keyboard(Movement direction, float deltaTime);
  void mouse(float xoffset, float yoffset, GLboolean constrainPitch = true);

  glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + front, up); }

private:
  void updateVectors();
};
