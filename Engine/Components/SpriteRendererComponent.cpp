#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Resources/ResourceManager.h"
#include "Engine.h"
#include "Framework/Scene.h"

#include <iostream>

namespace nu {
	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer) {

		if (m_texture) {
			renderer.DrawTexture(*m_texture,
				GetOwner()->GetTransform().position.x,
				GetOwner()->GetTransform().position.y,
				GetOwner()->GetTransform().rotation,
				GetOwner()->GetTransform().scale);
		}	
	}

	void SpriteRendererComponent::Read(const json::value_t& value){
		RendererComponent::Read(value);
		std::string textureName;
		JSON_READ_NAME(value, "texture", textureName);
		if (!textureName.empty()) {
			m_texture = Resources().Get<Texture>(textureName, Engine::Get().GetRenderer());
			if (!m_texture) {
				std::cerr << "Failed to Load texture: " << textureName << std::endl;
			}
		}

	}


    void SpriteRendererComponent::Update(float dt){
     
    }

	
}