#pragma once

#include "Texture.h"

#include <vector>
#include <array>
#include <string>

#include <glad/glad.h>

/*
EXPECTED LAYOUT FOR VERTEX POSITION AND COLOR:

std::vector<float> vertices
{
  //positon (3D)        //color for vertex (RGBA) //texture coords    //normals
  0.0f,  0.0f, 0.0f,    1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  0.0f,  0.0f, 0.0f,
  1.0f,  1.0f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 1.0f,  0.0f,  0.0f, 0.0f,
 -1.0f,  1.0f, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f,   1.0f, 1.0f,  0.0f,  0.0f, 0.0f,
 -1.0f, -1.0f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 1.0f,  0.0f,  0.0f, 0.0f,
  1.0f, -1.0f, 0.0f,    1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  0.0f,  0.0f, 0.0f,
  ...
}

std::vector<unsigned int> indices
{
  0, 1, 2,   // first triangle
  0, 4, 3    // second triangle
  ...
};

std::vector<float> texture
  {
    0.0f, 0.0f,  // lower-left corner
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
  };
*/

class Buffer
{
public:
  struct Attribute
  {
    unsigned int location{};
    int size{};
    int offset{};
  };

  Buffer(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::array<std::string_view, 2>& paths);
  Buffer(const std::vector<float>& vertices, const std::array<std::string_view, 2>& paths);
  ~Buffer();

  constexpr GLuint getVAO() const { return m_VAO; }
  constexpr GLsizei getStride() const { return 12 * sizeof(float); }
  template <typename T>
  constexpr std::size_t getSize(const std::vector<T>& vec) const { return vec.size() * sizeof(T); }
  constexpr GLuint getTexture(int x) const { return (x == 1) ? m_TO1 : m_TO2; }

  void remoteVAO(GLuint& VAO) const;
private:
  static constexpr Attribute m_position{ 0u, 3, 0 };
  static constexpr Attribute m_color{ 1u, 4, (sizeof(float) * 3) };
  static constexpr Attribute m_texture{ 2u, 2, (sizeof(float) * 7) };
  static constexpr Attribute m_normal{ 3u, 3, (sizeof(float) * 9) };

  GLuint m_VBO{};
  GLuint m_VAO{};
  GLuint m_EBO{};
  GLuint m_TO1{};
  GLuint m_TO2{};
};