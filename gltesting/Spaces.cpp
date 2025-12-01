#include "Spaces.h"
#include "Window.h"
#include "Camera.h"

Rotation::Rotation(const glm::vec3& axis, float angle)
  : m_axis{ axis }
  , m_angle{ angle }
{
  if (m_axis == glm::vec3{ 0.f, 0.f, 0.f })
    m_axis = glm::vec3{ 0.f, 1.f, 0.f };
}

void Spaces::update(Camera& camera, Window& window)
{
  getInstance().projection = glm::perspective(glm::radians(camera.fov), window.height() / window.width(), camera.nearPlane, camera.farPlane);
  getInstance().view = camera.getViewMatrix();
}

