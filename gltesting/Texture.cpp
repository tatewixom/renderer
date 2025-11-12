#include "Texture.h"

std::deque<Texture*> Texture::s_textureQueue{};
int Texture::s_activeUnits{};

Texture::Texture(const std::string_view path)
{
  if (s_textureQueue.size() < getMaxUnits())
  {
    m_assignedUnit = static_cast<int>(GL_TEXTURE0) + s_activeUnits;
    ++s_activeUnits; //increments one for counting active units

    load(path);

    s_textureQueue.push_front(this);
  }
  else if (s_textureQueue.size() >= getMaxUnits())
  {
    //removing back texture from active units
    m_assignedUnit = s_textureQueue.back()->m_assignedUnit;

    s_textureQueue.back()->m_assignedUnit = 0;
    s_textureQueue.pop_back();

    load(path);

    s_textureQueue.push_front(this);
  }
}

int Texture::use()
{
  if (m_assignedUnit == 0)
  {
    m_assignedUnit = s_textureQueue.back()->m_assignedUnit;
    glActiveTexture(static_cast<GLenum>(m_assignedUnit));
    glBindTexture(GL_TEXTURE_2D, m_id);

    s_textureQueue.back()->m_assignedUnit = 0;
    s_textureQueue.pop_back();
    s_textureQueue.push_front(this);

    return m_assignedUnit - static_cast<int>(GL_TEXTURE0);
  }
  else
    return m_assignedUnit - static_cast<int>(GL_TEXTURE0);
}

bool Texture::isRGBA(const std::string_view path)
{
  std::string_view fileExtensionName{ "png" }; //3 is the length if 'png'
  std::size_t start{ path.length() - fileExtensionName.length() };
  std::string sub{ path.substr(start, fileExtensionName.length()) };

  return sub == fileExtensionName;
}

void Texture::load(const std::string_view path)
{
  //loading and creating a texture
  glActiveTexture(static_cast<GLenum>(m_assignedUnit));
  glGenTextures(1, &m_id);
  glBindTexture(GL_TEXTURE_2D, m_id);

  //defining how opengl should render our pixels
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //first
  int width{}, height{}, channels{};
  unsigned char* data{ stbi_load(path.data(), &width, &height, &channels, 0) };

  if (!data)
    std::cerr << "ERROR::TEXTURE.CPP::LOAD()::DATA_CHAR_ARRAY_EMPTY\n";
  else
  {
    if (isRGBA(path))
    {
      //note that GL_RGBA is activated due to the image being a .png file
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
  }

  stbi_image_free(data);
}

GLint Texture::getMaxUnits()
{
  GLint maxUnits{};
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnits);

  return maxUnits;
}