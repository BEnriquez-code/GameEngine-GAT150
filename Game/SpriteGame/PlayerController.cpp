#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"


FACTORY_REGISTER(PlayerController)

void PlayerController::Start() {
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);

	m_spriteAnimatorRendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_spriteAnimatorRendererComponent);
}

void PlayerController::Update(float dt) {
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();
	float dir = 0.0f;

	switch (m_state) {
		case CharacterBase::State::Move:

			
			if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
			if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1.0f;


			if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
				velocity.y = -500.0f;
			}


			if (dir != 0.0f) {
				velocity.x = dir * 200.0f;
				m_spriteAnimatorRendererComponent->Play("run");
			}
			else if (velocity.y < 0.0f) {
				m_spriteAnimatorRendererComponent->Play("jump");
			}
			else {
				m_spriteAnimatorRendererComponent->Play("idle");
			}
			m_spriteAnimatorRendererComponent->SetFlipH(dir < 0.0f);

			if (nu::Engine::Get().GetInput().GetButtonDown(nu::Input::MouseButton::Left)) {
				m_state = CharacterBase::State::Attack;
				m_spriteAnimatorRendererComponent->Play("attack");
				m_spriteAnimatorRendererComponent->SetFlipH(dir < 0.0f);
			}

			break;
		case CharacterBase::State::Attack:
			if (m_spriteAnimatorRendererComponent->IsAnimationFinished()) {
				m_state = CharacterBase::State::Move;
			}

			break;
		case CharacterBase::State::Hit:
			break;
		case CharacterBase::State::Dead:
			break;
		default:
			break;
	}


	m_physicsComponent->SetVelocity(velocity);

	CharacterBase::Update(dt);
}

void PlayerController::OnCollision(nu::Actor* other) {

}

void PlayerController::Read(const nu::json::value_t& value) {
	CharacterBase::Read(value);
}