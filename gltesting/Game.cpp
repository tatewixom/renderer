#include "Game.h"
#include "World.h"
#include "CallBack.h"

#include <stb/stb_image.h>

#include <chrono>

namespace
{
  using clock_type = std::chrono::high_resolution_clock;
  auto lastTime = clock_type::now();
  int frames = 0;
  double fps = 0.0;
}

Game::Game()
{
  //stbi init
  stbi_set_flip_vertically_on_load(true);

  m_mouse.viewMode();

  glEnable(GL_DEPTH_TEST);
}

void Game::initialize()
{
  m_state.push(std::make_unique<World>(m_state, m_window, m_camera, m_mouse));
}

void Game::run()
{
  initialize();

  while (!glfwWindowShouldClose(m_window))
  {
    frames++;

    auto now = clock_type::now();
    std::chrono::duration<double> elapsed = now - lastTime;

    if (elapsed.count() >= 0.1) 
    {
      fps = frames / elapsed.count();
      m_window.title(std::to_string(fps));
      frames = 0;
      lastTime = now;
    }

    glfwPollEvents();
    m_mouse.update();
    m_camera.update(m_mouse);

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