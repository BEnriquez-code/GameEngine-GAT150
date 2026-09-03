#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Framework/Actor.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	Actor::Start();
	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_spriteAnimatorRendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_spriteAnimatorRendererComponent);
}

void EnemyController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();
	velocity.y += 500.0f * dt; // gravity
	m_physicsComponent->SetVelocity(velocity);
	if (velocity.x < 0.0f) {
		m_spriteAnimatorRendererComponent->SetFlipH(true);
	}
	else if (velocity.x > 0.0f) {
		m_spriteAnimatorRendererComponent->SetFlipH(false);
	}
	Actor::Update(dt);
}

void EnemyController::OnCollision(nu::Actor* other) {

}

void EnemyController::Read(const nu::json::value_t& value) {
	Actor::Read(value);
}