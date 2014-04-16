#include "BoxCollider.h"

BoxCollider::BoxCollider(engine::Transform &t, game::GameObject &g) :
Collider(BOX_COLLIDER, t, g, BOX)
{

}

BoxCollider::~BoxCollider() {}


