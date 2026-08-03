#include "Bullet.h"
#include "MathUtils.h"

#include <iostream>

void Bullet::Update(float dt) {
	nu::Vector2 forward{ 1.0f, 0.0f };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * m_speed;

	m_lifespan -= dt;	

	if (m_lifespan <= 0.0f) {
		SetDestroyed();
	}

	SetVelocity(velocity);

	Actor::Update(dt);
}