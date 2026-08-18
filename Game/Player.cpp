#include "Player.h"
#include "ResourceManager.h"
#include "Bullet.h"
#include "Assets.h"
#include "Renderer.h"
#include "Engine.h"
#include "Factory.h"
#include <iostream>

FACTORY_REGISTER(Player)

void Player::Update(float dt) {
    float thrust = 0.0f;
    float rotate = 0.0f;

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4)) nu::Engine::Get().GetAudio().PlaySound("test");
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1)) nu::Engine::Get().GetAudio().PlaySound("mario");
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2)) nu::Engine::Get().GetAudio().PlaySound("bass");
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3)) nu::Engine::Get().GetAudio().PlaySound("hee-hee");
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_6)) nu::Engine::Get().GetAudio().PlaySound("thrust");

   
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) {
        rotate = -180.0f;
        
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) { 
        rotate = +180.0f; 
    }

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) { 
        thrust = +m_speed;
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) { 
        thrust = -m_speed; 
    }

    SetRotation(m_transform.rotation + rotate * dt);


    nu::Vector2 forward{ 1, 0 }; // ->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
        BulletDesc bulletDesc;
        bulletDesc.name = "Bullet";
        bulletDesc.tag = "PlayerBullet";
        //bulletDesc.model = assets::bulletModel;
		bulletDesc.texture = nu::Resources().Get<nu::Texture>("Textures/bullet.png", nu::Engine::Get().GetRenderer());
        bulletDesc.transform = m_transform;
        bulletDesc.speed = 1000.0f;
        bulletDesc.lifespan = 2.0f;

        m_scene->AddActor(std::make_unique<Bullet>(bulletDesc));

    }

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }
    else {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }
    
    nu::Particle particle;
    particle.position = m_transform.position;
    particle.texture = nu::Resources().Get<nu::Texture>("Textures/particle.png", nu::Engine::Get().GetRenderer());
    particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
    particle.velocity = { nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

    
    Actor::Update(dt);

    
}


void Player::Draw(const nu::Renderer& renderer) const {
	Actor::Draw(renderer);
}

void Player::OnCollision(Actor* other) {
   if (other->GetTag() == "Enemy") {
       std::cout << "Player destrooyed" << std::endl;
       SetDestroyed();
        other->SetDestroyed();
   }
}