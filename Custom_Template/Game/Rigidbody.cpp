#include "Rigidbody.h"
#include "../Utilities/Time.h"
#include "../Utilities/Transform.h"
#include "../Utilities/Physics.h"

Rigidbody::Rigidbody(engine::Transform &t, game::GameObject &g) :
BaseComponent(RIGIDBODY, t, g),
m_vel(float2(0,0)),
m_mass(1.0f),
m_drag(0.0f),
m_useGravity(true),
m_isKinematic(false),
m_freezePositionX(false),
m_freezePositionY(false)
{

}
Rigidbody::~Rigidbody() {}

struct State
{
  float2 p;
  float2 v;
};

struct Derivative
{
  float2 dp;
  float2 dv;
};

Derivative Evaluate(const State &initial)
{
  Derivative output;
  output.dp = initial.v;
  output.dv = physics::g_gravity;
  return output;
}

Derivative Evaluate(const State &initial, float dt, const Derivative &d)
{
  State state;
  state.p = initial.p + d.dp*dt;
  state.v = initial.v + d.dv*dt;
  Derivative output;
  output.dp = state.v;
  output.dv = physics::g_gravity;
  return output;
}

void Integrate(State &state, float dt)
{
  Derivative a = Evaluate(state);
  Derivative b = Evaluate(state, dt*0.5f, a);
  Derivative c = Evaluate(state, dt*0.5f, b);
  Derivative d = Evaluate(state, dt, c);

  const float2 dpdt = (1.0f / 6.0f) * (a.dp + 2.0f*(b.dp + c.dp) + d.dp);
  const float2 dvdt = (1.0f / 6.0f) * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);

  state.p = state.p + dpdt*dt;
  state.v = state.v + dvdt*dt;
}

void Rigidbody::Update()
{
  if(m_isKinematic)
    return;

  const float dt = time::GetDeltaTime();

  State s;
  s.p = m_transform.position;
  s.v = m_vel;
  Integrate(s, dt);
  if(!m_freezePositionX) m_transform.position.x = s.p.x;
  if(!m_freezePositionY) m_transform.position.y = s.p.y;
  if(!m_freezePositionX) m_vel.x = s.v.x;
  if(!m_freezePositionY) m_vel.y = s.v.y;

  //float2 acc = m_useGravity ? physics::g_gravity : float2(0, 0);
  //m_vel += acc * dt * dt;
  //m_vel *= (1.0f - m_drag);
  //if(m_freezePositionX) m_vel.x = 0.0f;
  //if(!m_freezePositionY) m_vel.y = 0.0f;

  //float2 oldPos = m_transform.position;
  //m_transform.position += m_vel;
  //m_vel = m_transform.position - oldPos;
}
