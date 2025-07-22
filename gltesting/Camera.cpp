#include "Camera.h"

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

void Camera::keyboard(Movement direction, float deltaTime)
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

void Camera::mouse(float xoffset, float yoffset, GLboolean constrainPitch)
{
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch)
  {
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;
  }

  // update Front, Right and Up Vectors using the updated Euler angles
  updateVectors();
}

void Camera::updateVectors()
{
  glm::vec3 temp{};
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(temp);
  // also re-calculate the Right and Up vector
  right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  up = glm::normalize(glm::cross(right, front));
}