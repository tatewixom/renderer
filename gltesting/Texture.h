#pragma once

#include <iostream>

#include <glad/glad.h>

#include <stb/stb_image.h>

class Texture
{
public:
  Texture(const std::string_view path);

  GLint getID() const { return m_id; }
  std::string_view getPath() const { return m_path; }
  GLint getMaxUnits();
  int getLocation() const { return m_assignedUnit - static_cast<int>(GL_TEXTURE0); }

  bool isRGBA();

private:
  std::string_view m_path{}; //path to texture 
  GLuint m_id{}; //texture object id
  int m_assignedUnit{ static_cast<int>(GL_TEXTURE0) };

private:
  
  static int s_activeUnits;
};