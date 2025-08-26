#pragma once

#include "State.h"
#include "Interface.h"

class Window;
class Camera;

class World final : public IState
{
public:
  World(State& state, Window& window, Camera& camera)
    : IState{ state }
    , m_window{ window }
    , m_camera{ camera }
  {
    initialize();
  }

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

  std::unique_ptr<Interface> interface{ std::make_unique<Interface>(m_state, m_window, m_camera) };
};
