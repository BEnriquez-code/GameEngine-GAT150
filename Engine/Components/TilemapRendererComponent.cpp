#include "pch.h"
#include "TilemapRendererComponent.h"
#include "Core/Factory.h"
#include "Renderer/Tilemap.h"
#include "Physics/PhysicsBody.h"
#include "Engine.h"

namespace nu {
	FACTORY_REGISTER(TilemapRendererComponent)

	TilemapRendererComponent::TilemapRendererComponent(const TilemapRendererComponent& other){
		m_tilemapName = other.m_tilemapName;
	}

	void TilemapRendererComponent::Start(){
		m_tilemap = Resources().Get<Tilemap>(m_tilemapName, Engine::Get().GetRenderer());
	}

	void TilemapRendererComponent::Draw(const Renderer& renderer){

	}

	void TilemapRendererComponent::Read(const json::value_t& value){
		RendererComponent::Read(value);

		JSON_READ_NAME(value, "tilemap_ame", m_tilemapName);
	}

}



