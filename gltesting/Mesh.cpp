#include "Mesh.h"
#include "Random.h"

#include <iostream>

Mesh::Layout::Layout(const std::vector<Attribute>& newAttributes)
{
  glGenVertexArrays(1, &VAO);
  bind();

  attributes = newAttributes;
}

void Mesh::Layout::interpret()
{
  for (const auto& attrib : attributes)
  {
    glEnableVertexAttribArray(attrib.location);
    glVertexAttribPointer(attrib.location, attrib.size, GL_FLOAT, GL_FALSE, attrib.stride, (void*)(attrib.offset));
  }
}

void Mesh::Layout::instance() //add attribute location here & make overloaded instance() for automatic location
{
  std::size_t vec4Size{ sizeof(glm::vec4) };
  for (GLuint i{ 0 }; i < 4; ++i)
  {
    glEnableVertexAttribArray(4u + i);
    glVertexAttribPointer(4u + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * vec4Size));
    glVertexAttribDivisor(4u + i, 1); // advance per instance
  }

  //allow for definition of starting attribute location and later automatic attribute handling.
  //this will most likely be the source of most problems
}

void Mesh::Layout::instance(unsigned int location)
{
  std::size_t vec4Size{ sizeof(glm::vec4) };
  for (GLuint i{ 0 }; i < 4; ++i)
  {
    glEnableVertexAttribArray(4u + i);
    glVertexAttribPointer(location + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * vec4Size));
    glVertexAttribDivisor(location + i, 1); // advance per instance
  }
}

void Mesh::Buffer::send(const std::vector<float>& vertices)
{
  if (vertices.size() > 0)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(*vertices.data()), vertices.data(), GL_STATIC_DRAW);
  else
    std::cerr << "ERROR::MESH.CPP::MESH::BUFFER::SEND()::VERTICE_ARRAY_WITH_SIZE_BELOW_ONE\n";
}

void Mesh::Buffer::send(const std::vector<glm::mat4>& matrices)
{
  if (matrices.size() > 0)
    glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(*matrices.data()), matrices.data(), GL_STATIC_DRAW);
  else
    std::cerr << "ERROR::MESH.CPP::MESH::BUFFER::SEND()::MATRICE_ARRAY_WITH_SIZE_BELOW_ONE\n";
}

void Mesh::Element::send(const std::vector<unsigned int>& indices)
{
  if (indices.size() > 0)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(*indices.data()), indices.data(), GL_STATIC_DRAW);
  else
    std::cerr << "ERROR::MESH.CPP::MESH::ELEMENT::SEND()::INDICE_ARRAY_WITH_SIZE_BELOW_ONE\n";
}

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<Layout::Attribute>& attributes)
  : m_layout{ attributes }
  , m_buffer{ vertices }
  , m_element{ indices }
{
  m_layout.bind();
  m_layout.interpret();
}