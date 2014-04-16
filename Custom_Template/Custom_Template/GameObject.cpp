#include "GameObject.h"
#include "StringFunctions.h"

namespace game
{
  GameObject::~GameObject()
  {
    if(m_name != nullptr)
      delete m_name;
  }

  void GameObject::SetName(const char* name)
  {
    if(m_name != nullptr)
      delete[] m_name;
    m_name = str_funcs::StringDuplicate(name);
  }
}