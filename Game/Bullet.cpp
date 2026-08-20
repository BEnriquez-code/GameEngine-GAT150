#include "Bullet.h"
#include "MathUtils.h"
#include "Factory.h"

#include <iostream>

FACTORY_REGISTER(Bullet);

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

void Bullet::Read(const nu::json::value_t& value) {
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
	JSON_READ_NAME(value, "lifespan", m_lifespan);
}