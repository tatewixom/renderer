#pragma once

#include "File.h"

#include <iostream>
#include <string_view>
#include <utility>
#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//compiles shader programs
class Shader
{
public:
  enum Variables
  {
    projection,
    model, 
    view,
    ortho,
    mvp,
  };

  Shader(std::string_view vertex, std::string_view fragment);
  ~Shader();

  //implicity converts shader object to GLuint m_program when used in glUseProgram function (and like functions)
  operator GLuint() const { return m_program; }

  void destroyProgram() const { glDeleteProgram(m_program); }

  void compile(const GLuint shader, const char* contents);
  void link(GLuint program, GLuint vertex, GLuint fragment);

  void set(std::string_view var, glm::vec4 vec) const;
  void set(std::string_view var, glm::vec3 vec) const;
  void set(std::string_view var, glm::vec2 vec) const;
  void set(std::string_view var, float x) const;
  
  template <typename T>
  void set(const std::vector<std::pair<std::string_view, T>>& vec);

  void set(std::string_view var, int x) const;

  void set(Shader::Variables var, const glm::mat4& mat) const;

  void set(std::string_view var, const glm::mat4& mat) const;

  constexpr void activate() const { glUseProgram(m_program); }
  constexpr void deactivate() const { glUseProgram(0); }

  private:
  GLuint m_program{};
  GLuint m_vertex{};
  GLuint m_fragment{};
};

template<typename T>
inline void Shader::set(const std::vector<std::pair<std::string_view, T>>& vec)
{
  for (const auto& pair : vec)
    set(pair.first, pair.second);
}
