#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Framework/Actor.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	CharacterBase::Start();
	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_spriteAnimatorRendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_spriteAnimatorRendererComponent);
}

void EnemyController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();
	float dir = 0.0f;
	auto player = m_scene->FindByTag<Actor>("Player");
	if (player) {
		nu::Vector2 position = GetTransform().position;
		nu::Vector2 playerPosition = player->GetTransform().position;

		if (playerPosition.x < position.x) dir = -1.0f;
		else dir = 1.0f;
	}

	if (dir != 0.0f) {
		velocity.x = dir * 70.0f;
		m_spriteAnimatorRendererComponent->Play("run");
	}
	else {
		m_spriteAnimatorRendererComponent->Play("idle");
	}
	CharacterBase::Update(dt);
}

void EnemyController::OnCollision(nu::Actor* other) {

}

void EnemyController::Read(const nu::json::value_t& value) {
	CharacterBase::Read(value);
}