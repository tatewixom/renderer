#include "Collection.h"
#include "Random.h"

Collection::Collection(int count, const Object& object)
  : m_object{ object }
{
  if (count != 0 && count > 0)
  {
    float extra{ 1.5f };
    m_objectContainer.reserve(static_cast<std::size_t>(count * extra));

    add(count);
  }
  else
    std::cerr << "ERROR::COLLECTION.CPP::COLLECTION::INVALID_AMOUNT_OF_OBJECTS\n";
}

void Collection::add()
{
  m_objectContainer.push_back(createObject());
}

void Collection::add(int amount)
{
  for (std::size_t i{ 0 }; i < amount; ++i)
  {
    m_objectContainer.push_back(createObject());
  }
}

void Collection::sort()
{

}

glm::vec3 Collection::getRandomPosition(int min, int max)
{
  return glm::vec3{ static_cast<float>(Random::get(min * 1000, max * 1000)) / 1000.0f, static_cast<float>(Random::get(min * 1000, max * 1000)) / 1000.0f, static_cast<float>(Random::get(min * 1000, max * 1000)) / 1000.0f };
}

Object Collection::createObject()
{
  Object object{ m_object };
  object.position(getRandomPosition(-10, 10));
  return object;
}
