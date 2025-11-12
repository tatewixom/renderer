#include "World.h"
#include "Input.h"
#include "Window.h"
#include "Camera.h"
#include "Random.h"
#include "Mouse.h"
#include "Points.h"

#include <memory>

namespace
{
  //input processing
  float deltaTime{};
  float lastFrame{};

  Buffer buffer{ Points::Cube::vertices, Points::Cube::indices };

  Shader basic{ "basic.vs", "basic.fs" };
  Shader color{ "color.vs", "color.fs" };
  Shader light{ "light.vs", "light.fs" };
  Shader test{ "test.vs", "test.fs" };
  Shader instancing_spotlight{ "instancing_spotlight.vs", "instancing_spotlight.fs" };

  Ditto ditto
  {
    Points::Cube::vertices,
    Points::Cube::indices,
    std::vector<Mesh::Layout::Attribute>
    {
      Mesh::Layout::Attribute{ 0u, 3, 12 * sizeof(float), 0 },
      Mesh::Layout::Attribute{ 1u, 4, 12 * sizeof(float), (sizeof(float) * 3) },
      Mesh::Layout::Attribute{ 2u, 2, 12 * sizeof(float), (sizeof(float) * 7) },
      Mesh::Layout::Attribute{ 3u, 3, 12 * sizeof(float), (sizeof(float) * 9) }
    },
    instancing_spotlight
  };

  Collection cubes
  {
    10,
    Object
    {
      buffer, 
      glm::vec3{ 0.0f },
      Object::Material{ glm::vec3{ 1.0f, 0.5f, 0.31f }, glm::vec3{ 1.0f, 0.5f, 0.31f }, glm::vec3{ 0.5f, 0.5f, 0.5f }, 32.f }
    }
  };

  Object lights{ buffer, glm::vec3{ 0.0f }, Object::Material{} };

  Texture container{ "assets/container.jpg" };
  Texture awesomeFace{ "assets/awesomeface.png" };
  Texture steelbox{ "assets/container2.png" };
  Texture steelbox_specular{ "assets/container2_specular.png" };

  //glm::vec3 randomColor{ Random::get(10, 90), Random::get(10, 90), Random::get(10, 90), };
}

World::World(State& state, Window& window, Camera& camera, Mouse& mouse)
  : IState{ state }
  , m_window{ window }
  , m_camera{ camera }
  , m_mouse{ mouse }
{
  initialize();
}

void World::initialize()
{
  basic.activate();
  basic.set("texture1", container.use());
  basic.set("texture2", awesomeFace.use());
  basic.set("opacity", 0.2f);

  light.activate();
  light.set("color", glm::vec3{ 1.0, 1.0, 1.0 });

  color.activate();
  color.set("objectColor", glm::vec3{ 1.0f, 1.0f, 1.0f });
  
  color.set("material.diffuse", steelbox.use());
  color.set("material.specular", steelbox_specular.use());
  color.set("material.shininess", cubes.object().material().shininess);

  color.set("lightPoint.position", lights.position());
  color.set("lightPoint.ambient", glm::vec3{ 0.5f, 0.5f, 0.5f });
  color.set("lightPoint.diffuse", glm::vec3{ 0.5f, 0.5f, 0.5f });
  color.set("lightPoint.specular", glm::vec3{ 1.0f, 1.0f, 1.0f });
  color.set("lightPoint.constant", 1.0f);
  color.set("lightPoint.linear", 0.09f);
  color.set("lightPoint.quadratic", 0.032f);

  color.set("lightCaster.direction", glm::vec3{ -0.2f, -1.0f, -0.3f });
  color.set("lightCaster.ambient", glm::vec3{ 0.2f, 0.2f, 0.2f });
  color.set("lightCaster.diffuse", glm::vec3{ 0.5f, 0.5f, 0.5f });
  color.set("lightCaster.specular", glm::vec3{ 1.0f, 1.0f, 1.0f });

  instancing_spotlight.activate();
  instancing_spotlight.set("objectColor", glm::vec3{ 1.0f, 1.0f, 1.0f });

  instancing_spotlight.set("material.diffuse", steelbox.use());
  instancing_spotlight.set("material.specular", steelbox_specular.use());
  instancing_spotlight.set("material.shininess", cubes.object().material().shininess);

  instancing_spotlight.set("spotlight.position", lights.position());
  instancing_spotlight.set("spotlight.ambient", glm::vec3{ 0.1f, 0.1f, 0.1f });
  instancing_spotlight.set("spotlight.diffuse", glm::vec3{ 0.5f, 0.5f, 0.5f });
  instancing_spotlight.set("spotlight.specular", glm::vec3{ 1.0f, 1.0f, 1.0f });
  instancing_spotlight.set("spotlight.constant", 0.5f);
  instancing_spotlight.set("spotlight.linear", 0.09f);
  instancing_spotlight.set("spotlight.quadratic", 0.032f);
  instancing_spotlight.set("spotlight.direction", glm::vec3{ -0.2f, -1.0f, -0.3f });
  instancing_spotlight.set("spotlight.cutoff", glm::cos(glm::radians(35.0f)));
  instancing_spotlight.set("spotlight.outerCutoff", glm::cos(glm::radians(40.0f)));

  test.activate();
  test.set("texture1", steelbox.use());

  lights.scale(glm::vec3{ 0.2f });

  std::size_t amount{ 100000 };
  std::vector<glm::mat4> matrices(amount);
  std::vector<Ditto::Motions> motions{};
  motions.reserve(amount);
  for (std::size_t i{ 0 }; i < amount; ++i)
  {
    motions.push_back(
      Ditto::Motions
      { 
        glm::vec3{ Random::get(-100, 100), Random::get(-100, 100), Random::get(-100, 100) },
        glm::vec3{ 1.f },
        Ditto::Rotation{ glm::vec3{ Random::get(0, 10), Random::get(0, 10), Random::get(0, 10) }, static_cast<float>(Random::get(0, 36000)) / 100.f }
      });
  }

  ditto.sendInstances(matrices, motions, 4u);
}

void World::input()
{
  Input::processWindowEscape(m_window);

  //delta time
  float currentFrame{ static_cast<float>(glfwGetTime()) };
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  //moving camera
  const float cameraSpeed = 20.f * deltaTime; // adjust accordingly
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

  //cubes manipulation
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_G))
    cubes.add(5);
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_9))
    std::cout << cubes.size() << '\n';

  //moving light position
  const float objectSpeed{ 5.f * deltaTime };
  if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
    lights.position(lights.position() - glm::vec3{ 0.0f, 0.0f, 1.0f } * objectSpeed);
  if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    lights.position(lights.position() + glm::vec3{ 1.0f, 0.0f, 0.0f } * objectSpeed);
  if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
    lights.position(lights.position() - glm::vec3{ 1.0f, 0.0f, 0.0f } * objectSpeed);
  if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
    lights.position(lights.position() + glm::vec3{ 0.0f, 0.0f, 1.0f } * objectSpeed);
  if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
    lights.position(lights.position() + glm::vec3{ 0.0f, 1.0f, 0.0f } * objectSpeed);
  if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
    lights.position(lights.position() - glm::vec3{ 0.0f, 1.0f, 0.0f } * objectSpeed);

  //states
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_1))
    m_state.push(std::make_unique<World>(m_state, m_window, m_camera, m_mouse));
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_2))
    m_state.pop();
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_3))
    m_state.loopBelow();
}

void World::clear()
{
  //clearing screen and rendering
  glClearColor(0.06f, 0.06f, 0.06f, 0.f); //signature gray
  //glClearColor(0.f, 0.f, 0.f, 0.f); //black
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void World::update()
{
  Object::update(m_camera, m_window);
  Ditto::update(m_camera, m_window);

  color.activate();
  //color.set("lightPoint.position", m_camera.position);
  //color.set("viewPos", m_camera.position);

  instancing_spotlight.activate();
  instancing_spotlight.set("spotlight.position", m_camera.position);
  instancing_spotlight.set("spotlight.direction", m_camera.front);
  instancing_spotlight.set("viewPos", m_camera.position);

  //color.set("objectColor", glm::vec3{sin(randomColor.x + time), sin(randomColor.y + time), sin(randomColor.z + time)});

  cubes.sort(m_camera);

  for (auto& cube : cubes)
  {
    cube.rotate(Object::Rotation{ glm::vec3{ cube.position().y * 2.f, cube.position().z * 3.f, cube.position().x * 9.f }, static_cast<float>(glfwGetTime() * glm::radians(100.f) * 50) });
  }
}

void World::render()
{
  glfwPollEvents();

  //cubes.draw(color);
  //lights.draw(light);

  ditto.draw();

  m_interface->input();
  m_interface->loop();

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
