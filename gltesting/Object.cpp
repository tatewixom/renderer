#include "Object.h"
#include "Camera.h"
#include "Shader.h"
#include "Window.h"

Object::Spaces Object::s_spaces{};

void Object::move(const glm::vec3& position)
{
  m_position = position;
}

void Object::rotate(const Rotation& rotation)
{
  m_rotation = rotation;
}

void Object::scale(const glm::vec3& scalar)
{
  m_dimensions.scalar = scalar;
}

void Object::update(const Camera& camera, const Window& window)
{
  s_spaces.projection = glm::perspective(glm::radians(camera.fov), window.height() / window.width(), camera.nearPlane, camera.farPlane);
  s_spaces.view = camera.getViewMatrix();
}

void Object::draw(const Shader& shader) const
{
  s_spaces.model = glm::mat4{ 1.f };

  s_spaces.model = glm::translate(s_spaces.model, m_position);
  s_spaces.model = glm::rotate(s_spaces.model, m_rotation.angle(), m_rotation.axis());
  s_spaces.model = glm::scale(s_spaces.model, m_dimensions.scalar);

  s_spaces.mvp = glm::mat4{ s_spaces.projection * s_spaces.view * s_spaces.model };

  shader.activate();

  shader.set("mvp", s_spaces.mvp);
  shader.set(Shader::model, s_spaces.model);
  
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36); // 36 is the amount of vertices 
  glBindVertexArray(0);

  shader.deactivate();
}