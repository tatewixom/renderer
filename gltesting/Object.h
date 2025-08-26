#pragma once

#include "Buffer.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

class Camera;
class Shader;
class Window;

class Object
{
public:
  struct Material
  {
    glm::vec3 ambient{};
    glm::vec3 diffuse{};
    glm::vec3 specular{};
    float shininess{};
  };

  struct Spaces
  {
    glm::mat4 model{ 1.0f };
    glm::mat4 projection{ 1.0f };
    glm::mat4 view{ 1.0f };
    glm::mat4 mvp{ 1.0f };
  };

  struct Dimension
  {
    float x{};
    float y{};
    float z{};
    glm::vec3 scalar{ 1.f };
  };

  class Rotation
  {
  public:
    Rotation() = default;

    Rotation(const glm::vec3& axis, float angle)
      : m_axis{ axis }
      , m_angle{ angle }
    {
      if (m_axis == glm::vec3{ 0.f, 0.f, 0.f })
        m_axis = glm::vec3{ 0.f, 1.f, 0.f };
    }

    auto angle() const { return glm::radians(m_angle); }

    auto axis() const { return glm::normalize(m_axis); }

  private:
    glm::vec3 m_axis{ 0.f, 1.f, 0.f };
    float m_angle{ 0.f };
  };

  Object() = default;

  Object(const Buffer& buffer, glm::vec3 position, const Material& material)
    : m_position{ position }
    , m_material{ material }
    , m_VAO{ buffer.getVAO() }
  { }

  Object(const GLuint VAO, glm::vec3 position, const Material& material)
    : m_position{ position }
    , m_material{ material }
    , m_VAO{ VAO }
  { }

  //static object manipulation/initialization
  void move(const glm::vec3& direction);
  void rotate(const Rotation& rotation);
  void scale(const glm::vec3& scalar);

  //update function for camera
  static void update(const Camera& camera, const Window& window);

  //drawing
  void draw(const Shader& shader) const;

  //getting/setting position
  glm::vec3& position() { return m_position; }
  void position(const glm::vec3& position) { m_position = position; }

  //getting/setting dimensions
  Dimension& dimensions() { return m_dimensions; }

  //spaces access function
  Spaces& spaces() { return s_spaces; }

  //scaling
  glm::vec3& scalar() { return m_dimensions.scalar; }

protected:
  glm::vec3 m_position{};
  Material m_material{};
  GLuint m_VAO{};
  Dimension m_dimensions{};
  Rotation m_rotation{};

protected:
  //forward declaration
  static Spaces s_spaces;
};