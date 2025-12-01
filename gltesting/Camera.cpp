#include "Camera.h"
#include "Mouse.h"

Camera::Camera(float vfov, glm::vec3 vposition, float vspeed, float vsensitivity)
  : position{ vposition }
  , front{ 0.0f, 0.0f, -1.0f }
  , up{ 0.0f, 1.0f, 0.0f }
  , direction{ glm::normalize(vposition - glm::vec3{ 0.0f, 0.0f, 0.0f}) }
  , right{ glm::normalize(glm::cross(up, direction)) }
  , fov{ vfov }
  , speed{ vspeed }
  , sensitivity{ vsensitivity }
{ }

void Camera::move(Movement direction, float deltaTime)
{
  float velocity = speed * deltaTime;
  if (direction == FORWARD)
    position += front * velocity;
  if (direction == BACKWARD)
    position -= front * velocity;
  if (direction == LEFT)
    position -= right * velocity;
  if (direction == RIGHT)
    position += right * velocity;
}

void Camera::update(Mouse& mouse)
{
  Mouse::Position cameraMovement{ mouse.getOffset() };

  if (mouse.isDisabled())
  {
    yaw += static_cast<float>(cameraMovement.x * sensitivity);
    pitch += static_cast<float>(cameraMovement.y * sensitivity);

    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;

    //calculating camera vector
    glm::vec3 direction{};
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
  }
}