#include "Rigidbody.h"
#include "Time.h"
#include "Transform.h"
#include "Physics.h"

Rigidbody::Rigidbody(engine::Transform &t, game::GameObject &g) :
BaseComponent(RIGIDBODY, t, g),
m_prevPos(t.position),
m_mass(1.0f),
m_drag(0.0f),
m_useGravity(true),
m_isKinematic(false),
m_freezePositionX(false),
m_freezePositionY(false)
{

}

Rigidbody::~Rigidbody() {}

void Rigidbody::Update()
{
  if(m_isKinematic)
    return;

  const float dt = time::GetDeltaTime();

  float2 acc = m_useGravity ? physics::g_gravity : float2(0, 0);

  float2 vel = (m_transform.position - m_prevPos) + (acc * dt * dt);
  vel *= (1.0f - m_drag);
  if(m_freezePositionX) vel.x = 0.0f;
  if(m_freezePositionY) vel.y = 0.0f;

  float2 newPrevPos = m_transform.position;
  m_transform.position += vel;
  m_prevPos = newPrevPos;
}
