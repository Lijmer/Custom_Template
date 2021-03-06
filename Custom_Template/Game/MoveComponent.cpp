#include "MoveComponent.h"
#include "../Utilities/Transform.h"
#include "../Utilities/float2.h"
#include "../Utilities/time.h"
#include "../Utilities/Constants.h"
#include "../Game/GameObject.h"
#include "TextRenderer.h"

void MoveComponent::Update()
{
  //m_transform.m_position += float2(time::GetDeltaTime(), time::GetDeltaTime()) * 100.0f;

  TextRenderer* t = (TextRenderer*)m_gameObject.GetComponent(TEXT_RENDERER);
  //m_transform.position = float2(10.f, 10.0f);
  static float fps;
  fps = .99f * fps + .01f * (1.0f / time::GetDeltaTime());
  char str[64];
  sprintf_s(str, "FPS: %d ####", (int)fps);
  t->SetString(str);
}
