#pragma once

#include "Shader.h"
#include "Space.h"

#include <glad/glad.h>

class Cube
{
public:
  enum Type
  {
    solid,
    lamp,
  };

  Cube() = default;

  Cube(const glm::vec3& position)
    : m_position{ position }
  {}

  Cube(const glm::vec3& position, const GLuint VAO)
    : m_position{ position }
    , m_VAO{ VAO }
  {}

  //movers
  void initialize(); //moves cube to initial predefined position
  void move(const glm::vec3& direction);
  void rotate(float angle, const glm::vec3& axis);
  void scale(glm::vec3 factor);

  void draw() const;
  void draw(const Shader& shader) const;

  //setters
  void setVAO(GLuint VAO) { m_VAO = VAO; }

  //getters
  Type& type() { return m_type; }

  static glm::mat4& getModel() { return m_space.model(); }
  static glm::mat4& getProjection() { return m_space.projection(); }
  static glm::mat4& getView() { return m_space.view(); }

  glm::vec3 position() const { return m_position; }
  void position(const glm::vec3& position) { m_position = position; }

private:
  glm::vec3 m_position{};
  GLuint m_VAO{};
  Type m_type{};
  std::vector<float> m_vertices;

  //forward declaration
  static Space m_space;
};

