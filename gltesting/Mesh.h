#pragma once

#include "Texture.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <array>

struct Vertex
{
  glm::vec3 position{};
  glm::vec2 texture{};
  glm::vec3 normal{};
};

struct Layout_t
{
  struct Attribute
  {
    unsigned int location{};
    int size{};
    int stride{};
    int offset{};
  };

  Layout_t() = default;

  void initialize(const std::array<Attribute, 3>& newAttributes);

  void gen() { glGenVertexArrays(1, &VAO); }
  void bind() const { glBindVertexArray(VAO); }
  void interpret(const std::array<Attribute, 3>& newAttributes);

  unsigned int VAO{};
};

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

  void initialize(const std::vector<Attribute>& newAttributes);

  void bind() const { glBindVertexArray(VAO); }
  void interpret();
  void instance();
  void instance(unsigned int location);

  std::vector<Attribute> attributes{};
  unsigned int VAO{};
};

struct VertexBuffer_t
{
  VertexBuffer_t() = default;

  void initialize(const std::vector<Vertex>& vertices);

  void gen() { glGenBuffers(1, &VBO); }
  void bind() const { glBindBuffer(GL_ARRAY_BUFFER, VBO); }
  void send(const std::vector<Vertex>& vertices);

  unsigned int VBO{};
};

struct VertexBuffer
{
  VertexBuffer() = default;

  void initialize(const std::vector<float>& vertices);

  void gen() { glGenBuffers(1, &VBO); }
  void bind() const { glBindBuffer(GL_ARRAY_BUFFER, VBO); }
  void send(const std::vector<float>& vertices);
  void send(const std::vector<glm::mat4>& matrices);

  unsigned int VBO{};
};

struct Element
{
  Element() = default;

  void initialize(const std::vector<unsigned int>& indices);

  void gen() { glGenBuffers(1, &EBO); }
  void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); }
  void send(const std::vector<unsigned int>& indices);

  unsigned int EBO{};
  std::size_t indiceCount{};
};

class Shader;

class Mesh_t
{
public:
  void initialize(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::array<Layout_t::Attribute, 3>& attributes, std::vector<Texture> textures);

  void draw(Shader& shader);

protected:
  Layout_t m_layout{};
  VertexBuffer_t m_buffer{};
  Element m_element{};
  std::vector<Texture> textures{};
};

class Mesh
{
public:
  void initialize(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<Layout::Attribute>& attributes);

protected:
  Layout m_layout{};
  VertexBuffer m_buffer{};
  Element m_element{};
};