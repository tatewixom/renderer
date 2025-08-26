#include "State.h"

void State::initialize()
{
  if (!m_states.empty())
    m_states.back()->initialize();
}

void State::input()
{
  if (!m_states.empty())
    m_states.back()->input();
}

void State::update()
{
  if (!m_states.empty())
    m_states.back()->update();
}

void State::render()
{
  if (!m_states.empty())
    m_states.back()->render();
}

void State::loop()
{
  if (!m_states.empty())
    m_states.back()->loop();
}

void State::clean()
{
  if (!m_states.empty())
    m_states.back()->clean();
}

void State::push(std::unique_ptr<IState> newState)
{
  m_states.push_back(std::move(newState));
}

void State::pop()
{
  if (!m_states.empty() && m_states.size() > 1)
    m_states.pop_back();
}

void State::loopBelow()
{
  if (!m_states.empty() && m_states.size() > 1)
    m_states[m_states.size() - 2]->loop();
}
