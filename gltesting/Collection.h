#pragma once

#include "Object.h"

class Collection
{
public:
  Collection(int count, const Object& object);

  Object& operator[](int i) { return m_objectContainer[i]; }

  void add();
  void add(int amount);

  void sort();

  glm::vec3 getRandomPosition(int min, int max);

  auto begin() { return m_objectContainer.begin(); }
  auto end() { return m_objectContainer.end(); }

  int size() const { return static_cast<int>(m_objectContainer.size()); }

private:
  Object createObject();

  Object m_object{};
  std::vector<Object> m_objectContainer{};
};

