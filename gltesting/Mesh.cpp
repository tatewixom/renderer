#include "Mesh.h"
#include "Random.h"
#include "Shader.h"
#include "Spaces.h"

#include <iostream>

void Layout_t::initialize(const std::array<Attribute, 3>& newAttributes)
{
  gen();
  bind();
  interpret(newAttributes);
}

void Layout_t::interpret(const std::array<Attribute, 3>& newAttributes)
{
  for (const auto& attrib : newAttributes)
  {
    glEnableVertexAttribArray(attrib.location);
    glVertexAttribPointer(attrib.location, attrib.size, GL_FLOAT, GL_FALSE, attrib.stride, reinterpret_cast<void*>(attrib.offset));
  }
}

void Layout::initialize(const std::vector<Attribute>& newAttributes)
{
  glGenVertexArrays(1, &VAO);
  bind();

  attributes = newAttributes;
}

void Layout::interpret()
{
  for (const auto& attrib : attributes)
  {
    glEnableVertexAttribArray(attrib.location);
    glVertexAttribPointer(attrib.location, attrib.size, GL_FLOAT, GL_FALSE, attrib.stride, reinterpret_cast<void*>(attrib.offset));
  }
}

void Layout::instance() //add attribute location here & make overloaded instance() for automatic location
{
  std::size_t vec4Size{ sizeof(glm::vec4) };
  for (GLuint i{ 0 }; i < 4; ++i)
  {
    glEnableVertexAttribArray(4u + i);
    glVertexAttribPointer(4u + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(i * vec4Size));
    glVertexAttribDivisor(4u + i, 1); // advance per instance
  }

  //allow for definition of starting attribute location and later automatic attribute handling.
  //this will most likely be the source of most problems
}

void Layout::instance(unsigned int location)
{
  std::size_t vec4Size{ sizeof(glm::vec4) };
  for (GLuint i{ 0 }; i < 4; ++i)
  {
    glEnableVertexAttribArray(4u + i);
    glVertexAttribPointer(location + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(i * vec4Size));
    glVertexAttribDivisor(location + i, 1); // advance per instance
  }
}

void VertexBuffer_t::initialize(const std::vector<Vertex>& vertices)
{
  gen();
  bind();
  send(vertices);
}

void VertexBuffer_t::send(const std::vector<Vertex>& vertices)
{
  if (vertices.size() > 0)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
  else
    std::cerr << "ERROR::MESH.CPP::VERTEXBUFFER_T::SEND()::VERTICE_ARRAY_WITH_SIZE_BELOW_ONE\n";
}

void VertexBuffer::initialize(const std::vector<float>& vertices)
{
  glGenBuffers(1, &VBO);
  bind();
  send(vertices);
}

void VertexBuffer::send(const std::vector<float>& vertices)
{
  if (vertices.size() > 0)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(*vertices.data()), vertices.data(), GL_STATIC_DRAW);
  else
    std::cerr << "ERROR::MESH.CPP::VERTEXBUFFER::SEND()::VERTICE_ARRAY_WITH_SIZE_BELOW_ONE\n";
}

void VertexBuffer::send(const std::vector<glm::mat4>& matrices)
{
  if (matrices.size() > 0)
    glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(*matrices.data()), matrices.data(), GL_STATIC_DRAW);
  else
    std::cerr << "ERROR::MESH.CPP::VERTEXBUFFER::SEND()::MATRICE_ARRAY_WITH_SIZE_BELOW_ONE\n";
}

void Element::initialize(const std::vector<unsigned int>& indices)
{
  gen();
  bind();
  send(indices);

  indiceCount = indices.size();
}

void Element::send(const std::vector<unsigned int>& indices)
{
  if (indices.size() > 0)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(*indices.data()), indices.data(), GL_STATIC_DRAW);
  else
    std::cerr << "ERROR::MESH.CPP::ELEMENT::SEND()::INDICE_ARRAY_WITH_SIZE_BELOW_ONE\n";
}

void Mesh_t::initialize(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::array<Layout_t::Attribute, 3>& attributes, std::vector<Texture> textures)
{
  m_layout.gen();
  m_layout.bind();

  m_buffer.gen();
  m_buffer.bind();
  m_buffer.send(vertices);

  m_element.gen();
  m_element.bind();
  m_element.send(indices);
  m_element.indiceCount = indices.size();

  m_layout.interpret(attributes);

  this->textures = std::move(textures);
}

void Mesh_t::draw(Shader& shader)
{
  for (std::size_t i{ 0 }; i < textures.size(); ++i)
  {

  }

  Spaces& spaces{ Spaces::getInstance() };

  spaces.model = glm::mat4{ 1.f };

  glm::vec3 position{ 0.f, 0.f, 0.f };
  Rotation rotation{};
  Dimension dimensions{};
  dimensions.scalar = glm::vec3{ 5.f };

  spaces.model = glm::translate(spaces.model, position);
  spaces.model = glm::rotate(spaces.model, rotation.angle(), rotation.axis());
  spaces.model = glm::scale(spaces.model, dimensions.scalar);

  spaces.mvp = glm::mat4{ spaces.projection * spaces.view * spaces.model };

  shader.activate();
  shader.set("mvp", spaces.mvp);

  glBindVertexArray(m_layout.VAO);
  glDrawElements(GL_TRIANGLES, m_element.indiceCount, GL_UNSIGNED_INT, 0);
}

void Mesh::initialize(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<Layout::Attribute>& attributes)
{
  m_layout.initialize(attributes);
  m_layout.bind();
  m_layout.interpret();

  m_buffer.initialize(vertices);

  m_element.initialize(indices);
}

