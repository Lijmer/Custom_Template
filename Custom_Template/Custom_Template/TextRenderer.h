#ifndef INCLUDED_TEXT_RENDERER_H
#define INCLUDED_TEXT_RENDERER_H

#include "BaseComponent.h"

class TextRenderer : public BaseComponent
{
public:
  TextRenderer(engine::Transform& t, game::GameObject &g) :
    BaseComponent(TEXT_RENDERER, t, g),
    m_string(nullptr) {}
  ~TextRenderer();

  void SetString(const char* str);

  virtual void Update();
  
  const char* GetString() const { return m_string; }

private:
  char* m_string;
};

#endif//INCLUDED_TEXT_RENDERER_H
