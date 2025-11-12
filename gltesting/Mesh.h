#pragma once

#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Shader;

class Mesh
{
public:
  struct Layout
  {
    struct Attribute
    {
      unsigned int location{};
      int size{};
      int stride{};
      int offset{};
    };

    Layout() = default;

    Layout(const std::vector<Attribute>& newAttributes);

    void bind() const { glBindVertexArray(VAO); }
    void interpret();
    void instance();
    void instance(unsigned int location);

    std::vector<Attribute> attributes{};
    unsigned int VAO{};
  };

  struct Buffer
  {
    Buffer() = default;

    Buffer(const std::vector<float>& vertices)
    {
      glGenBuffers(1, &VBO);
      bind();
      send(vertices);
    }

    void gen() { glGenBuffers(1, &VBO); }
    void bind() const { glBindBuffer(GL_ARRAY_BUFFER, VBO); }
    void send(const std::vector<float>& vertices);
    void send(const std::vector<glm::mat4>& matrices);

    unsigned int VBO{};
  };

  struct Element
  {
    Element() = default;

    Element(const std::vector<unsigned int>& indices)
    {
      glGenBuffers(1, &EBO);
      bind();
      send(indices);

      indiceCount = indices.size();
    }

    void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); }
    void send(const std::vector<unsigned int>& indices);

    unsigned int EBO{};
    std::size_t indiceCount{};
  };

  Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<Layout::Attribute>& attributes);

  Mesh(const Mesh& mesh) = delete;

protected:
  Layout m_layout{};
  Buffer m_buffer{};
  Element m_element{};
};