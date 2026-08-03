#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "SpaceGame.h"

#include <iostream>

void Enemy::Update(float dt) {
	Player* player = m_scene->GetActorByName<Player>("Player");
	if (player) {
		nu::Vector2 direction = player->GetTransform().position - m_transform.position;

		float angle = direction.Angle();
		SetRotation(angle * nu::math::RadToDeg);

		nu::Vector2 forward{ 1, 0 };

		forward = forward.Rotate(m_transform.rotation * nu::math::DegToRad);
		AddVelocity(forward * m_speed * dt);
	}

	float thrust = 0.0f;

	float rotate = 0.0f;

	nu::Vector2 forward{ 1, 0 }; // ->
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * thrust;
	AddVelocity(velocity * dt);

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
	if (other->GetTag() == "PlayerBullet") {
		SetDestroyed();
		other->SetDestroyed();

		int enemyBaseValue = 100;		
		((SpaceGame*)m_scene->GetGame())->AddKillStreakPoints(enemyBaseValue);


		for (int i = 0; i < 100; i++)
		{
			nu::Particle particle;
			particle.position = m_transform.position;
			particle.color = { 1.0f, 1.0f, 1.0f };
			particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
			particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

			nu::Engine::Get().GetPS().AddParticle(particle);
		}
	}
	else if (other->GetTag() == "Player") {
		SetDestroyed();
		other->SetDestroyed();
	}
}