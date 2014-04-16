#include "TextRenderer.h"
#include "StringFunctions.h"
#include "renderer.h"

TextRenderer::~TextRenderer()
{
  if(m_string != nullptr)
    delete[] m_string;
}

void TextRenderer::SetString(const char* str)
{
  if(m_string != nullptr)
    delete[] m_string;
  m_string = str_funcs::StringDuplicate(str);
}

void TextRenderer::Update()
{
  engine::renderer::AddRenderElement(this);
}
