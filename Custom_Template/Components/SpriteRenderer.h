#ifndef INCLUDED_SPRITE_RENDERER
#define INCLUDED_SPRITE_RENDERER

#include "BaseComponent.h"
#include "../Renderer/SpriteID.h"


class SpriteRenderer : public BaseComponent
{
public:
  SpriteRenderer(engine::Transform&, game::GameObject&);
  virtual ~SpriteRenderer();
  virtual void Update();

  void SetSprite(engine::SPR::SpriteID ID) { m_sprite = ID; }

  const engine::SPR::SpriteID GetSpriteID() const { return m_sprite; }
private:
  engine::SPR::SpriteID m_sprite;
};

#endif//INCLUDED_SPRITE_RENDERER
