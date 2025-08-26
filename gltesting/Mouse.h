#pragma once

class Window;

class Mouse
{
public:
  struct Position
  {
    float x{};
    float y{};

    friend bool operator==(const Position& pos1, const Position& pos2);
  };

  struct Button
  {
    int button{};
    int action{};
  };

  Position& getPosition() { return m_position; }
  Position& getOffset() { return m_offset; }
  Position& getLastPosition() { return m_lastPosition; }
  Button& getButton() { return m_button; }

  void center(Window& window);

  void viewMode(Window& window);
  void selectionMode(Window& window);

  bool isButtonPressed(int mouseButton) const;
  bool isDisabled(Window& window) const;

  void setLastPosition(); //sets last position from being in view mode

private:
  Position m_position{};
  Position m_offset{};
  Position m_lastPosition{};
  Button m_button{};
};

extern Mouse mmouse;