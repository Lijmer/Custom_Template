#include "TestComponent.h"

#include "../Game/GameObject.h"
#include "TextRenderer.h"


void TestComponent::Update()
{

}

void TestComponent::FixedUpdate()
{
  //m_transform.m_position += float2(time::GetDeltaTime(), time::GetDeltaTime()) * 100.0f;
  LARGE_INTEGER li = m_lastUpdate;
  QueryPerformanceCounter(&m_lastUpdate);
  float fups = 1.0f / ((float)(m_lastUpdate.QuadPart - li.QuadPart) / (float)(m_ticksPS.QuadPart));

  TextRenderer* t = (TextRenderer*)m_gameObject.GetComponent(TEXT_RENDERER);
  //m_transform.position = float2(10.f, 10.0f);

  char str[64];
  sprintf_s(str, "FUPS: %f ####", fups);
  t->SetString(str);
}
