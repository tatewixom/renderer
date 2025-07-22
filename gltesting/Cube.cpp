#include "Cube.h"

Space Cube::m_space{};

void Cube::initialize()
{
  move(m_position);
}

void Cube::move(const glm::vec3& direction)
{
  m_space.model() = glm::translate(m_space.model(), direction);
}

void Cube::rotate(float angle, const glm::vec3& axis)
{
  m_space.model() = glm::rotate(m_space.model(), angle, axis);
}

void Cube::scale(glm::vec3 factor)
{
  m_space.model() = glm::scale(m_space.model(), factor);
}

void Cube::draw() const
{
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36); // 36 is the amount of vertices 
  glBindVertexArray(0);

  m_space.modelReset();
}

void Cube::draw(const Shader& shader) const
{
  shader.activate();

  shader.set(Shader::projection, m_space.projection());
  shader.set(Shader::view, m_space.view());
  shader.set(Shader::model, m_space.model());

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36); // 36 is the amount of vertices 
  glBindVertexArray(0);

  m_space.modelReset();
}
