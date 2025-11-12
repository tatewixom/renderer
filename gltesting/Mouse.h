#pragma once

class Window;

class Mouse
{
public:
  struct Position
  {
    double x{};
    double y{};

    friend bool operator==(const Position& pos1, const Position& pos2);
    friend Position operator-(const Position& pos1, const Position& pos2);
  };

  struct Button
  {
    int button{};
    int action{};
  };

  Mouse(Window& window);

  Position& getPosition() { return m_position; }
  Position& getOffset() { return m_offset; }
  Position& getLastPosition() { return m_lastPosition; }
  Button& getButton() { return m_button; }

  void center();

  void viewMode();
  void selectionMode();

  bool isButtonPressed(int mouseButton) const;
  bool isDisabled() const;

  void setLastPosition(); //sets last position from being in view mode

private:
  Window& m_window;
  Position m_position{};
  Position m_offset{};
  Position m_lastPosition{};
  Button m_button{};
};