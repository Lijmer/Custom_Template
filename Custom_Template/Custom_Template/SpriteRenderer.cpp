#include "SpriteRenderer.h"
#include "SpriteDatabase.h"
#include "Renderer.h"

SpriteRenderer::SpriteRenderer(engine::Transform& t, game::GameObject &g) :
BaseComponent(SPRITE_RENDERER, t, g) {}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::Update()
{
  engine::renderer::AddRenderElement(this);
}

const engine::Sprite& SpriteRenderer::GetSprite() const
{
  return engine::sprite_database::GetSprite(m_sprite);
}
