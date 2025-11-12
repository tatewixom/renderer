#pragma once

#include "State.h"
#include "Ditto.h"
#include "Collection.h"
#include "Interface.h"
#include "Object.h"
#include "Shader.h"
#include "Buffer.h"

class Window;
class Camera;
class Mouse;

class World final : public IState
{
public:
  World(State& state, Window& window, Camera& camera, Mouse& mouse);

  ~World() override
  {
    clean();
  }

  void initialize() override;
  void input() override;
  void clear();
  void update() override;
  void render() override;
  void loop() override;
  void clean() override;

private:
  Window& m_window;
  Camera& m_camera;
  Mouse& m_mouse;

  std::unique_ptr<Interface> m_interface{ std::make_unique<Interface>(m_state, m_window, m_camera, m_mouse) };
};
