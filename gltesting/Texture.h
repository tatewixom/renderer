#pragma once

#include <iostream>
#include <deque>

#include <glad/glad.h>

#include <stb/stb_image.h>

class Texture
{
public:
  Texture(const std::string_view path);

  GLint getID() const { return m_id; }
  int getLocation() const { return m_assignedUnit - static_cast<int>(GL_TEXTURE0); }

  int use();

private:
  bool isRGBA(const std::string_view path);

  void load(const std::string_view path);

  GLint getMaxUnits();

private:
  GLuint m_id{}; //texture object id
  int m_assignedUnit{};

private:
  static std::deque<Texture*> s_textureQueue;
  static int s_activeUnits;
};