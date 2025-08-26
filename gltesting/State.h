#pragma once

#include <deque>
#include <memory>
#include <iostream>

class State;

class IState
{
public:
  explicit IState(State& state)
    : m_state{ state }
  { }

  virtual ~IState() = default;

  virtual void initialize() = 0;
  virtual void input() = 0;
  virtual void update() = 0;
  virtual void render() = 0;
  virtual void loop() = 0;
  virtual void clean() = 0;

protected:
  State& m_state;
};

class State
{
public:
  State() = default;

  //base functions
  void initialize();
  void input();
  void update();
  void render();
  void loop();
  void clean();
  void push(std::unique_ptr<IState> newState);
  void pop();

  //specialty functions
  void loopBelow();
private:
  std::deque<std::unique_ptr<IState>> m_states{};
};

class Temporary final : public IState
{
public:
  Temporary(State& state)
    : IState{ state }
  {
    initialize();
  }

  ~Temporary() override = default;

  void initialize() override {}
  void input() override {}
  void update() override {}
  void render() override {}
  void loop() override {}
  void clean() override {}
};

/* 
Example derived class:

class Example final : public IState
{
public:
  Example(State& state)
    : IState{ state }
  {
    initialize();
  }

  ~Example() override = default;

  void initialize() override {}
  void update() override {}
  void render() override {}
  void clean() override {}
};
*/