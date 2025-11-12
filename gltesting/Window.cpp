#include "Window.h"
#include "Callback.h"

#include <iostream>
#include <filesystem>

#include <stb/stb_image.h>

Window::Window(const char* title, float widthRatio, float heightRatio, GLFWmonitor* screenMode, GLFWwindow* share)
  : m_widthRatio{ widthRatio }
  , m_heightRatio{ heightRatio }
{
  //glfw init
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  const GLFWvidmode* monitor{ glfwGetVideoMode(glfwGetPrimaryMonitor()) };
  
  //finding ratio related to screen width
  m_width = static_cast<int>(monitor->width / m_widthRatio);

  m_height = static_cast<int>(m_width - (m_width / m_heightRatio));

  //centering window
  int finalPosX{ (monitor->width / 2) - (m_width / 2) };
  int finalPosY{ (monitor->height / 2) - (m_height / 2) };

  glfwWindowHint(GLFW_POSITION_X, finalPosX);
  glfwWindowHint(GLFW_POSITION_Y, finalPosY);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  m_window = glfwCreateWindow(m_width, m_height, title, screenMode, share);

  if (!m_window)
  {
    std::cerr << "ERROR::MAIN.CPP::WINDOW()::FAILURE_IN_WINDOW_CREATION\n";
    glfwTerminate();
  }
  else
  {
    //setting current context to window
    glfwMakeContextCurrent(m_window);

    //v-sync turned off
    glfwSwapInterval(0);

    //loading GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cerr << "ERROR::MAIN.CPP::WINDOW()::FAILURE_IN_INITIALIZING_GLAD\n";
      glfwTerminate();
    }

    //setting window icon
    std::filesystem::path icon{ "assets/container.jpg" };

    GLFWimage images[1]{};
    images[0].pixels = stbi_load(icon.string().data(), &images[0].width, &images[0].height, 0, 4); //rgba channels 
    glfwSetWindowIcon(m_window, 1, images);
    stbi_image_free(images[0].pixels);

    //setting callbacks
    glfwSetFramebufferSizeCallback(m_window, Callback::framebuffer);
    glfwSetWindowRefreshCallback(m_window, Callback::refresh);
  }
}

void Window::title(std::string_view title)
{
  glfwSetWindowTitle(m_window, title.data());
}
