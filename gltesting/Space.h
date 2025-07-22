#pragma once

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Space
{
public:
  Space()
    : m_model{ 1.0f }
    , m_projection{ 1.0f }
    , m_view{ 1.0f }
  { }

  glm::mat4& model() { return m_model; }
  glm::mat4& projection() { return m_projection; }
  glm::mat4& view() { return m_view; }

  void modelReset() { m_model = 1.0f; }

  void update();
private:
  glm::mat4 m_model{};
  glm::mat4 m_projection{};
  glm::mat4 m_view{};
};

