#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string_view>

class Window
{
public:
  Window(const char* title, float widthRatio = 2.0f, float heightRatio = 6.0, GLFWmonitor* screenMode = nullptr, GLFWwindow* share = nullptr);

  ~Window() { glfwTerminate(); }

  //implicit conversion from Window to GLFWwindow* (carefully use)
  operator GLFWwindow* () const { return m_window; }

  GLFWwindow* getWindow() { return m_window; }
  float width() const { int width{}; glfwGetWindowSize(m_window, &width, nullptr); return static_cast<float>(width); }
  float height() const { int height{}; glfwGetWindowSize(m_window, nullptr, &height); return static_cast<float>(height); }

  void size(int width, int height) { glViewport(0, 0, width, height); }
  void close() { glfwSetWindowShouldClose(m_window, true); }

  void title(std::string_view title);

private:
  GLFWwindow* m_window{};
  int m_width{};
  int m_height{};

  float m_widthRatio{};
  float m_heightRatio{};
};