#include "Game.h"

#include "Random.h"

Game game{};

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

  /*
  std::vector<glm::vec3> position
  {
    glm::vec3{ 0.0f,  0.0f,  0.0f },
    glm::vec3{ 2.0f,  0.0f, -2.0f }


    glm::vec3{-1.5f, -2.2f, -2.5f },
    glm::vec3{-3.8f, -2.0f, -12.3f },
    glm::vec3{ 2.4f, -0.4f, -3.5f },
    glm::vec3{-1.7f,  3.0f, -7.5f },
    glm::vec3{ 1.3f, -2.0f, -2.5f },
    glm::vec3{ 1.5f,  2.0f, -2.5f },
    glm::vec3{ 1.5f,  0.2f, -1.5f },
    glm::vec3{-1.3f,  1.0f, -1.5f }

  };
  */
}

class Cubes
{
public:
  enum Position
  {
    random,
  };

  explicit Cubes(int amount, GLuint VAO = 0, Position position = random)
  {
    if (!(amount == 0))
    {
      float extra{ 1.25f };
      m_cubes.reserve(static_cast<std::size_t>(amount * extra));

      for (std::size_t i{ 0 }; i < amount; ++i)
        m_cubes.push_back(Cube{});

      setVAO(VAO);

      place(position);
    }
  }

  Cube& operator[](int i) { return m_cubes[i]; }

  void place(Position position)
  {
    if (position == random)
    {
      int minPos{ -5 };
      int maxPos{ 5 };

      for (auto& cube : m_cubes)
        cube.position(glm::vec3{ Random::get(minPos, maxPos), Random::get(minPos, maxPos), Random::get(minPos, maxPos) });
    }
  }

  void add(int minPos = -5, int maxPos = 5)
  {
    m_cubes.push_back(Cube{});
    m_cubes.back().setVAO(m_VAO);
    m_cubes.back().position(glm::vec3{ Random::get(minPos, maxPos), Random::get(minPos, maxPos), Random::get(minPos, maxPos) });
  }

  void draw(const Shader& shader)
  {
    if (m_cubes.size() != 0)
      for (auto& cube : m_cubes)
        cube.draw(shader);
  }

  auto begin() { return m_cubes.begin(); }
  auto end() { return m_cubes.end(); }

  void reseatVAO(GLuint VAO) 
  {
    m_VAO = VAO;

    setVAO(VAO); 
  }

private:
  void setVAO(GLuint VAO)
  {
    m_VAO = VAO;

    if (m_cubes.size() != 0)
      for (auto& cube : m_cubes)
        cube.setVAO(VAO);
  }

  std::vector<Cube> m_cubes{};
  GLuint m_VAO{};
};

namespace
{
  //input processing
  float deltaTime{};
  float lastFrame{};

  //initializing buffers and shaders
  std::array<std::string_view, 2> texturePaths{ "assets/container.jpg", "assets/awesomeface.png" };

  Buffer buffer{ Points::vertices, texturePaths };

  Shader basic{ "basic.vs", "basic.fs" };
  Shader color{ "color.vs", "color.fs" };
  Shader light{ "light.vs", "light.fs" };

  GLuint lightVAO{};

  Cubes cubes{ 30, buffer.getVAO() };
  Cubes lights{ 1 };

  const std::vector<std::pair<std::string_view, glm::vec3>> lightColors{ { "objectColor", glm::vec3{ 0.6f, 0.5f, 1.0f } }, { "lightColor", glm::vec3{ 1.0f, 1.0f, 1.0f } } };

  glm::vec3 randomColor{ Random::get(0, 90), Random::get(0, 90), Random::get(0, 90), };
}

Game::Game()
{
  //stbi init
  stbi_set_flip_vertically_on_load(true);

  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //setting input mode

  glfwSetFramebufferSizeCallback(m_window, Callback::framebuffer);
  glfwSetCursorPosCallback(m_window, Callback::mouse);
  glfwSetScrollCallback(m_window, Callback::scroll);
  glfwSetWindowRefreshCallback(m_window, Callback::refresh);

  glEnable(GL_DEPTH_TEST);
}

void Game::initialize()
{
  //using shader program
  const std::vector<std::pair<std::string_view, int>> shaderTextures{ { "texture1", 0 }, { "texture2", 1 } };

  basic.activate();
  basic.set(shaderTextures);
  basic.set("opacity", 0.2f);
  basic.deactivate();

  light.activate();
  light.set("color", glm::vec3{ 1.0, 1.0, 1.0 });
  light.deactivate();

  color.activate();
  color.set(lightColors);
  color.deactivate();

  //initializing cubes
  buffer.remoteVAO(lightVAO);
  lights.reseatVAO(lightVAO);
}

void Game::processInput()
{
  //input handling and calculations
  Input::process(m_window);

  //delta time
  float currentFrame{ static_cast<float>(glfwGetTime()) };
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

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
}

void Game::clear()
{
  //clearing screen and rendering
  glClearColor(0.f, 0.f, 0.f, 0.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::update()
{
  color.activate();
  color.set("lightPos", lights[0].position());
  color.set("viewPos", m_camera.position);
  color.deactivate();

  Cube::getProjection() = glm::perspective(glm::radians(m_camera.fov), m_window.height() / m_window.width(), m_camera.nearPlane, m_camera.farPlane);
  Cube::getView() = m_camera.getViewMatrix();
}

void Game::render()
{
  processInput();

  clear();

  for (auto& cube : cubes)
  {
    cube.initialize();

    color.activate();
    float time{ static_cast<float>(sin(glfwGetTime())) };
    color.set(lightColors[0].first, glm::vec3{ sin(randomColor.x + time), sin(randomColor.y + time), sin(randomColor.z + time) });
    color.deactivate();

    float angle1{ 20 * static_cast<float>(cube.position().x) };
    float angle2{ static_cast<float>(glfwGetTime()) * glm::radians(50.0f) };
    cube.rotate(angle1, glm::vec3{ 1.f, 0.5f, 0.0f });
    cube.rotate(angle2, glm::vec3{ 0.35f, 0.9f, 0.4f });

    cube.draw(color);
  }

  for (auto& cube : lights)
  {
    cube.initialize();

    cube.scale(glm::vec3(0.2f));

    cube.draw(light);
  }

  //swaping buffers
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

void Game::run()
{
  initialize();

  while (!glfwWindowShouldClose(m_window))
  {
    update();

    render();
  }
}

//MAIN QUEST: work on collision between the camera and objects
// 
//SIDE QUEST: make a class meant for holding array of cubes. I.e. a cube manager
//SIDE QUEST: make a floor. should have collision, so the camera can walk around on the floor
// 
//Cleaned up the render loop even further. Also set the window icon.