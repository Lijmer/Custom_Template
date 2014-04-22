#include "SpriteRenderer.h"
#include "../Renderer/SpriteDatabase.h"
#include "../Renderer/Renderer.h"

SpriteRenderer::SpriteRenderer(engine::Transform& t, game::GameObject &g) :
BaseComponent(SPRITE_RENDERER, t, g) {}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::Update()
{
  engine::renderer::AddRenderElement(this);
}

