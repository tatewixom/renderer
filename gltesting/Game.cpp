#include "Game.h"
#include "World.h"
#include "CallBack.h"

#include <stb/stb_image.h>

Game game{};

Game::Game()
{
  //stbi init
  stbi_set_flip_vertically_on_load(true);

  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //setting input mode

  glfwSetFramebufferSizeCallback(m_window, Callback::framebuffer);
  glfwSetCursorPosCallback(m_window, Callback::mouse);
  glfwSetScrollCallback(m_window, Callback::scroll);
  glfwSetMouseButtonCallback(m_window, Callback::mouseButton);
  glfwSetWindowRefreshCallback(m_window, Callback::refresh);

  glEnable(GL_DEPTH_TEST);
}

void Game::initialize()
{
  m_state.push(std::make_unique<World>(m_state, m_window, m_camera));
}

void Game::run()
{
  initialize();

  while (!glfwWindowShouldClose(m_window))
  {
    m_state.input();

    m_state.loop();
  }
}

//MAIN QUEST: work on collision between the camera and objects
// 
//NOTE: there should be some correlation as to how the Texture and Object class are related. 
//So far, the only relation they have is the same shader they are using. 
// 
//SIDE QUEST: have set function for Shader class compatible with Texture class
//SIDE QUEST: make a floor. should have collision, so the camera can walk around on the floor
// 
//Finally created an object class that can represent anything with vertices
//Also cleaned up Game.cpp file from useless classes and redundancies 