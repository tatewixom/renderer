#include "World.h"
#include "Shader.h"
#include "Buffer.h"
#include "Collection.h"
#include "Input.h"
#include "Window.h"
#include "Camera.h"
#include "Random.h"

#include <memory>

namespace Points
{
  //cube vertices
  std::vector<float> vertices
  {
    //position            //color                 //texture    //normals
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
  };

  std::vector<unsigned int> indices
  {
    0, 1, 3,   // first triangle
    1, 2, 3,   // second triangle 
  };
}

namespace
{
  //input processing
  float deltaTime{};
  float lastFrame{};

  Buffer buffer{ Points::vertices };

  Shader basic{ "basic.vs", "basic.fs" };
  Shader color{ "color.vs", "color.fs" };
  Shader light{ "light.vs", "light.fs" };

  Collection cubes{ 40, Object{ buffer, glm::vec3{ 0.0f }, Object::Material{} } };
  Collection lights{ 1, Object{ buffer.remoteVAO(), glm::vec3{ 0.0f }, Object::Material{} } };

  Texture container{ "assets/container.jpg" };
  Texture awesomeFace{ "assets/awesomeface.png" };

  glm::vec3 randomColor{ Random::get(10, 90), Random::get(10, 90), Random::get(10, 90), };
}

void World::initialize()
{
  //using shader program
  basic.activate();
  basic.set("texture1", container.getLocation());
  basic.set("texture2", awesomeFace.getLocation());
  basic.set("opacity", 0.2f);
  basic.deactivate();

  light.activate();
  light.set("color", glm::vec3{ 1.0, 1.0, 1.0 });
  light.deactivate();

  color.activate();
  color.set("objectColor", glm::vec3{ 0.6f, 0.5f, 1.0f });
  color.set("lightColor", glm::vec3{ 1.0f, 1.0f, 1.0f });
  color.deactivate();

  for (auto& cube : lights)
    cube.scale(glm::vec3{ 0.2f });
}

void World::input()
{
  Input::processWindowEscape(m_window);

  //delta time
  float currentFrame{ static_cast<float>(glfwGetTime()) };
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  //moving camera
  const float cameraSpeed = 5.f * deltaTime; // adjust accordingly
  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    m_camera.position += cameraSpeed * m_camera.front;
  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    m_camera.position -= cameraSpeed * m_camera.front;
  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    m_camera.position -= glm::normalize(glm::cross(m_camera.front, m_camera.up)) * cameraSpeed;
  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    m_camera.position += glm::normalize(glm::cross(m_camera.front, m_camera.up)) * cameraSpeed;
  if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    m_camera.position += m_camera.up * cameraSpeed;
  if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    m_camera.position -= m_camera.up * cameraSpeed;

  //adding cubes
  if (glfwGetKey(m_window, GLFW_KEY_G) == GLFW_PRESS)
    cubes.add();

  //moving light position
  const float objectSpeed{ 5.f * deltaTime };
  if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
    lights[0].position() -= glm::vec3{ 0.0f, 0.0f, 1.0f } * objectSpeed;
  if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    lights[0].position() += glm::vec3{ 1.0f, 0.0f, 0.0f } * objectSpeed;
  if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
    lights[0].position() -= glm::vec3{ 1.0f, 0.0f, 0.0f } * objectSpeed;
  if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
    lights[0].position() += glm::vec3{ 0.0f, 0.0f, 1.0f } * objectSpeed;
  if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
    lights[0].position() += glm::vec3{ 0.0f, 1.0f, 0.0f } * objectSpeed;
  if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
    lights[0].position() -= glm::vec3{ 0.0f, 1.0f, 0.0f } * objectSpeed;

  //states
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_1))
    m_state.push(std::make_unique<World>(m_state, m_window, m_camera));
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_2))
    m_state.pop();
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_3))
    m_state.loopBelow();
}

void World::clear()
{
  //clearing screen and rendering
  glClearColor(0.2f, 0.2f, 0.2f, 0.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void World::update()
{
  color.activate();
  color.set("lightPos", lights[0].position());
  color.set("viewPos", m_camera.position);
  float time{ static_cast<float>(sin(glfwGetTime())) };
  color.set("objectColor", glm::vec3{sin(randomColor.x + time), sin(randomColor.y + time), sin(randomColor.z + time)});
  color.deactivate();

  Object::update(m_camera, m_window);

  for (auto& cube : cubes)
  {
    cube.rotate(Object::Rotation{ glm::vec3{ 1.f, 0.f, 0.f }, static_cast<float>(glfwGetTime() * glm::radians(100.f) * 50) });
  }
}

void World::render()
{
  glfwPollEvents();

  for (auto& cube : cubes)
  {
    cube.draw(color);
  }

  for (auto& cube : lights)
  {
    cube.draw(light);
  }

  interface->input();
  interface->loop();

  //swaping buffers
  glfwSwapBuffers(m_window);
}

void World::loop()
{
  update();

  clear();
  render();
}

void World::clean()
{
  
}
