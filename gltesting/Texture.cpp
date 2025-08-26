#include "Texture.h"

int Texture::s_activeUnits{};

Texture::Texture(const std::string_view path)
  : m_path{ path }
{
  if (s_activeUnits < getMaxUnits())
  {
    m_assignedUnit += s_activeUnits; 
    ++s_activeUnits; //increments one for counting active units

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
    unsigned char* data{ stbi_load(m_path.data(), &width, &height, &channels, 0) };

    if (!data)
      std::cerr << "ERROR::TEXTURE.CPP::TEXTURE::DATA_CHAR_ARRAY_EMPTY\n";
    else
    {
      if (isRGBA())
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
  else
  {
    std::cerr << "ERROR::TEXTURE.CPP::TEXTURE::NO_HANDLING_FOR_MAX_TEXTURE_UNITS_EXCEEDED_IMPLEMENTED\n";
  }
}

GLint Texture::getMaxUnits()
{
  GLint maxUnits{};
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnits);

  return maxUnits;
}

bool Texture::isRGBA()
{
  std::string_view fileExtensionName{ "png" }; //3 is the length if 'png'
  std::size_t start{ m_path.length() - fileExtensionName.length() };
  std::string sub{ m_path.substr(start, fileExtensionName.length()) };

  return sub == fileExtensionName;
}

