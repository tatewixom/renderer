#include "Interface.h"
#include "Callback.h"
#include "Input.h"
#include "Collection.h"
#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Mouse.h"

Interface::Element::Space Interface::Element::s_spaces{};

namespace Points
{
  Object::Dimension bd{ 700.f, 400.f };

  std::vector<float> backdrop
  {
     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     bd.x, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     bd.x, bd.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     bd.x, bd.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     0.0f, bd.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
  };

  Object::Dimension cb{ 500.f, 50.f };

  std::vector<float> controlBar
  {
     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     cb.x, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     cb.x, cb.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     cb.x, cb.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     0.0f, cb.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
  };
}

namespace
{
  Buffer backgroundBuffer{ Points::backdrop };

  Shader shader{ "interface.vs", "interface.fs" };

  Interface::Element background{ backgroundBuffer, glm::vec2{ 0.0f }, Interface::Element::Dimension{ Points::bd.x,  Points::bd.y } };
  Interface::Element grabBar{ backgroundBuffer, glm::vec2{ 0.0f }, Interface::Element::Dimension{ Points::bd.x,  Points::bd.y } };
}

void Interface::initialize()
{
  grabBar.scalar(glm::vec2{ 1.f, 0.1f });

  background.position(glm::vec2{ 0.0f , m_window.height() - background.dimensions().height() });
  grabBar.position(background, glm::vec2{ 0.0f, background.dimensions().height() - grabBar.dimensions().height() });
}

void Interface::input()
{
  if (Input::isKeyJustPressed(m_window, GLFW_KEY_0))
  {
    if (glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
      mmouse.selectionMode(m_window);
    else
      mmouse.viewMode(m_window);
  }

  if (Input::isKeyJustPressed(m_window, GLFW_KEY_9))
  {
    std::cout << "Background Position: (" << background.position().x << ", " << background.position().y << ")\n";
  }

  if (!mmouse.isDisabled(m_window) && mmouse.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) &&
    grabBar.hitbox().isIntersecting(mmouse.getPosition().x, m_window.height() - mmouse.getPosition().y))
  {
    background.position(glm::vec2{ background.position().x + mmouse.getOffset().x, background.position().y + mmouse.getOffset().y });
    grabBar.position(background, glm::vec2{ 0.0f, background.dimensions().height() - grabBar.dimensions().height() });
      //need to make a set of logic that has the window move in whatever direction the mouse moves in the same amount of units and doesn't lag behind 
  }
}

void Interface::update()
{
  Element::update(m_window);
}

void Interface::render()
{
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  shader.activate();
  shader.set("color", glm::vec4{ 0.f, 0.f, 0.f, 0.5f });
  shader.deactivate();

  background.draw(shader);

  shader.activate();
  shader.set("color", glm::vec4{ 0.28f, 0.29f, 0.30f, 1.0f });
  shader.deactivate();

  grabBar.draw(shader);

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
}

void Interface::loop()
{
  update();

  render();
}

void Interface::clean()
{

}

void Interface::Element::dimensions(const Dimension& dimensions)
{
  m_dimensions = dimensions;

  m_hitbox.area.x2 = m_dimensions.width();
  m_hitbox.area.y2 = m_dimensions.height();
}

void Interface::Element::draw(const Shader& shader) const
{
  s_spaces.model = glm::mat4{ 1.f };

  s_spaces.model = glm::translate(s_spaces.model, glm::vec3{ m_position.x, m_position.y, 0.f });
  s_spaces.model = glm::scale(s_spaces.model, m_dimensions.scalar);

  s_spaces.mvp = glm::mat4{ s_spaces.ortho * s_spaces.model };

  shader.activate();

  shader.set("mvp", s_spaces.mvp);

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6); // 36 is the amount of vertices 
  glBindVertexArray(0);

  shader.deactivate();
}

void Interface::Element::position(const glm::vec2& position)
{
  m_position = position;

  m_hitbox.area = Hitbox::Area{ m_position.x, m_position.y, m_position.x + m_dimensions.width(), m_position.y + m_dimensions.height() };
}

void Interface::Element::position(Element& element, const glm::vec2& relativePosition)
{
  m_position.x = element.position().x + relativePosition.x;
  m_position.y = element.position().y + relativePosition.y;

  m_hitbox.area = Hitbox::Area{ m_position.x, m_position.y, m_position.x + m_dimensions.width(), m_position.y + m_dimensions.height() };
}

void Interface::Element::center(Element& element)
{
  position(glm::vec2{ element.position().x + ((element.dimensions().width() / 2) * element.scalar().x) - ((dimensions().width() / 2) * m_dimensions.scalar.x),
    element.position().y + ((element.dimensions().height() / 2) * element.scalar().y) - ((dimensions().height() / 2) * m_dimensions.scalar.y) });
}

void Interface::Element::update(Window& window)
{
  s_spaces.ortho = glm::ortho(0.0f, window.width(), 0.0f, window.height(), -1.0f, 1.0f);
}

bool Interface::Element::Hitbox::isIntersecting(const glm::vec2& point) const
{
  if ((point.x > area.x1 && point.x < area.x2) && (point.y > area.y1 && point.y < area.y2)) // keep in mind w = x1 and x = x2
    return true;

  return false;
}

bool Interface::Element::Hitbox::isIntersecting(const float x, const float y) const
{
  if ((x > area.x1 && x < area.x2) && (y > area.y1 && y < area.y2))
    return true;

  return false;
}

bool Interface::Element::Hitbox::isIntersecting(const Element& element)
{
  return false;
}
