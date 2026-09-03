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

		if (!m_tilemap){
			std::cerr << "Could not load tilename " << m_tilemapName << std::endl;
			return;
		}

		// set tile transform current owner (actor) transform 
		Transform transform = GetOwner()->GetTransform();

		// define physics bodies 
		PhysicsBody::PhysicsBodyDef bodyDef;
		bodyDef.isDynamic = false;	// doesn't move (not dynamic) 
		bodyDef.actor = GetOwner();	// set actor for collision

		// iterate through layers	 

		for (auto& layer : m_tilemap->GetLayers()){
			// if layer doesn't have collision, skip physics body creation 
			if (!layer.hasCollision) continue;

			for (int i = 0; i < layer.data.size(); i++) {

				int tileId = layer.data[i];

				if (tileId == 0) continue;

				// set source rect from id 
				Rect sourceRect = m_tilemap->GetTileRect(layer, tileId);

				// set position from owner transform position + tile position * owner transform scale 
				transform.position = GetOwner()->GetTransform().position + (m_tilemap->GetTilePosition(layer, i) * transform.scale);


				// size of physics body is tehe source rect 
				Vector2 size{ sourceRect.w, sourceRect.h };



				// create physics body and add to physics bodies container 
				auto physicsBody = std::make_unique<PhysicsBody>(transform, size, bodyDef, Engine::Get().GetPhysics());

				m_physicsBodies.push_back(std::move(physicsBody));
			}
		}

		Transform ownerTransform = GetOwner()->GetTransform();
		for (const auto& zone : m_tilemap->GetGravityZones()){
			Tilemap::GravityZone worldZone;
			worldZone.bounds = Rect{
				ownerTransform.position.x + zone.bounds.x * ownerTransform.scale,
				ownerTransform.position.y + zone.bounds.y * ownerTransform.scale,
				zone.bounds.w * ownerTransform.scale,
				zone.bounds.h * ownerTransform.scale
			};
			worldZone.direction = zone.direction;
			m_gravityZones.push_back(worldZone);
		}


	}

	void TilemapRendererComponent::Draw(const Renderer& renderer){

		// iterate through layers 
		for (auto& layer : m_tilemap->GetLayers()){

			// get layer data (array of tile ids) 
			for (int i = 0; i < layer.data.size(); i++){

				int tileId = layer.data[i];


				if (tileId == 0) continue; // don't draw if tile ids = 0 

				// get source rect of tile id 
				Rect sourceRect = m_tilemap->GetTileRect(layer, tileId);

				// set position from owner (actor) transform position + tile position * transform scale 
				Transform transform = GetOwner()->GetTransform();

				Vector2 position = transform.position + m_tilemap->GetTilePosition(layer, i) * transform.scale;

				// draw tile texture 

				renderer.DrawTexture(*layer.texture, sourceRect, position.x, position.y, transform.rotation, transform.scale);

			}

		}

	}


	void TilemapRendererComponent::Read(const json::value_t& value){
		RendererComponent::Read(value);

		JSON_READ_NAME(value, "tilemap_name", m_tilemapName);
	}

	Vector2 TilemapRendererComponent::GetNearestTilePosition(const Vector2& worldPos){

		float bestDistSq = FLT_MAX;
		Vector2 bestDir{ 0.0f, 0.0f };
		for (const auto& zone : m_gravityZones){
			float closestX = math::Clamp(worldPos.x, zone.bounds.x, zone.bounds.x + zone.bounds.w);
			float closestY = math::Clamp(worldPos.y, zone.bounds.y, zone.bounds.y + zone.bounds.h);
			float dx = worldPos.x - closestX;
			float dy = worldPos.y - closestY;
			float distSq = dx * dx + dy * dy;
			if (distSq < bestDistSq){
				bestDistSq = distSq;
				bestDir = zone.direction;
			}
		}
		return bestDir;
		
	}

}



