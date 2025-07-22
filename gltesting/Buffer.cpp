#include "Buffer.h"

//for texture loading
#include <stb/stb_image.h>

Buffer::Buffer(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::array<std::string_view, 2>& paths)
{
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, getSize(vertices), vertices.data(), GL_STATIC_DRAW);

  //generating vertex array object
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  //creating an element array buffer to store indices in to tell opengl how to draw rectangle
  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, getSize(indices), indices.data(), GL_STATIC_DRAW);

  //creating preferred settings for telling opengl how to connect data
  glEnableVertexAttribArray(m_position.location);
  glVertexAttribPointer(m_position.location, m_position.size, GL_FLOAT, GL_FALSE, getStride(), (void*)(m_position.offset)); //fix warning at last parameter

  //telling opengl how to interpret colors
  glEnableVertexAttribArray(m_color.location);
  glVertexAttribPointer(m_color.location, m_color.size, GL_FLOAT, GL_FALSE, getStride(), (void*)(m_color.offset)); //fix warning at last parameter

  //telling opengl how to interpret textures
  glEnableVertexAttribArray(m_texture.location);
  glVertexAttribPointer(m_texture.location, m_texture.size, GL_FLOAT, GL_FALSE, getStride(), (void*)(m_texture.offset));


  //loading and creating a texture
  glActiveTexture(GL_TEXTURE0); // activates texture unit 0 for use (usually around 16 units) 0 is usually default
  glGenTextures(1, &m_TO1);
  glBindTexture(GL_TEXTURE_2D, m_TO1);

  //defining how opengl should render our pixels
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //first
  int width{}, height{}, channels{};
  unsigned char* data{ stbi_load(paths[0].data(), &width, &height, &channels, 0)};

  if (!data)
    std::cerr << "ERROR::TEXTURE.CPP::GENERATE::DATA_CHAR_ARRAY_EMPTY\n";
  else
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  stbi_image_free(data);

  //second
  glActiveTexture(GL_TEXTURE1);
  glGenTextures(1, &m_TO2);
  glBindTexture(GL_TEXTURE_2D, m_TO2);

  //defining how opengl should render our pixels
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  data = stbi_load(paths[1].data(), &width, &height, &channels, 0);

  if (!data)
    std::cerr << "ERROR::TEXTURE.CPP::GENERATE::DATA_CHAR_ARRAY_EMPTY\n";
  else
  {
    //note that GL_RGBA is activated due to the image being a .png file
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  stbi_image_free(data);
}

Buffer::Buffer(const std::vector<float>& vertices, const std::array<std::string_view, 2>& paths)
{
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, getSize(vertices), vertices.data(), GL_STATIC_DRAW);

  //generating vertex array object
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  //creating preferred settings for telling opengl how to connect data
  glEnableVertexAttribArray(m_position.location);
  glVertexAttribPointer(m_position.location, m_position.size, GL_FLOAT, GL_FALSE, getStride(), (void*)(m_position.offset)); //fix warning at last parameter
  glEnableVertexAttribArray(0); //disable

  //telling opengl how to interpret colors
  glEnableVertexAttribArray(m_color.location);
  glVertexAttribPointer(m_color.location, m_color.size, GL_FLOAT, GL_FALSE, getStride(), (void*)(m_color.offset)); //fix warning at last parameter
  glEnableVertexAttribArray(0); //disable

  //telling opengl how to interpret textures
  glEnableVertexAttribArray(m_texture.location);
  glVertexAttribPointer(m_texture.location, m_texture.size, GL_FLOAT, GL_FALSE, getStride(), (void*)(m_texture.offset));
  glEnableVertexAttribArray(0); //disable

  glEnableVertexAttribArray(m_normal.location);
  glVertexAttribPointer(m_normal.location, m_normal.size, GL_FLOAT, GL_FALSE, getStride(), (void*)(m_normal.offset));
  glEnableVertexAttribArray(0); //disable

  //loading and creating a texture
  glActiveTexture(GL_TEXTURE0); // activates texture unit 0 for use (usually around 16 units) 0 is usually default
  glGenTextures(1, &m_TO1);
  glBindTexture(GL_TEXTURE_2D, m_TO1);

  //defining how opengl should render our pixels
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //first
  int width{}, height{}, channels{};
  unsigned char* data{ stbi_load(paths[0].data(), &width, &height, &channels, 0) };

  if (!data)
    std::cerr << "ERROR::TEXTURE.CPP::GENERATE::DATA_CHAR_ARRAY_EMPTY\n";
  else
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  stbi_image_free(data);

  //second
  glActiveTexture(GL_TEXTURE1);
  glGenTextures(1, &m_TO2);
  glBindTexture(GL_TEXTURE_2D, m_TO2);

  //defining how opengl should render our pixels
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  data = stbi_load(paths[1].data(), &width, &height, &channels, 0);

  if (!data)
    std::cerr << "ERROR::TEXTURE.CPP::GENERATE::DATA_CHAR_ARRAY_EMPTY\n";
  else
  {
    //note that GL_RGBA is activated due to the image being a .png file
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  stbi_image_free(data);
}

Buffer::~Buffer()
{
  glDeleteBuffers(1, &m_VBO);
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_EBO);
}

void Buffer::remoteVAO(GLuint& VAO) const 
{
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // we only need to bind to the VBO, the container's VBO's data already contains the data.
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  // set the vertex attribute 
  glEnableVertexAttribArray(m_position.location);
  glVertexAttribPointer(m_position.location, m_position.size, GL_FLOAT, GL_FALSE, getStride(), (void*)(m_position.offset));
  glEnableVertexAttribArray(0);
}
