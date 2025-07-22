#pragma once

#include <iostream>
#include <filesystem>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stb/stb_image.h>

class Window
{
public:
  Window(const char* title, float widthRatio = 2.0f, float heightRatio = 6.0, GLFWmonitor* screenMode = nullptr, GLFWwindow* share = nullptr);

  ~Window() { glfwTerminate(); }

  //implicit conversion from Window to GLFWwindow* (carefully use)
  operator GLFWwindow* () const { return m_window; }

  GLFWwindow* getWindow() { return m_window; }
  constexpr float width() const { return static_cast<float>(m_width); }
  constexpr float height() const { return static_cast<float>(m_height); }

  void size(int width, int height) { glViewport(0, 0, width, height); }
  void close() { glfwSetWindowShouldClose(m_window, true); }

private:
  GLFWwindow* m_window{};
  int m_width{};
  int m_height{};

  float m_widthRatio{};
  float m_heightRatio{};
};