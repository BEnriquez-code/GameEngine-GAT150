#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Factory.h"

namespace nu {

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		actor->m_scene = this;
		m_pendingActors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors() {
		m_actors.clear();
	}

	bool Scene::Load(const std::string& sceneName){
		json::document_t document;
		if (json::Load("Data/scene.json", document)) {
			if (JSON_HAS_NAME(document, "actors")) {
				for (auto& actorValue : document["actors"].GetArray()) {


					std::string typeName;
					JSON_READ_NAME(actorValue, "type", typeName);

					auto actor = Factory::Instance().Create<Actor>(typeName);

					if (!actor) {
						std::cerr << "Failed to create actor: " << typeName << std::endl;
						continue;
					}
					actor->Read(actorValue);

					bool prototype = false;
					JSON_READ(actorValue, prototype);


					if (prototype) {
						std::string name;
						JSON_READ(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>("PlayerPrototype", std::move(actor));
					}
					else {
						AddActor(std::move(actor));
					}
					
				}
			}
			return true;
		}
		else {
			return false;
		}
		
	}

	void Scene::Update(float dt) {
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}
		UpdateCollisions();
		//remove destroyed actors
		std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });
		

		// ADD PENDING ACTORS
		for (auto& actor : m_pendingActors) {
			m_actors.push_back(std::move(actor));
		}


		//m_actors.insert(m_actors.end(), m_pendingActors.begin(), m_pendingActors.end());
		m_pendingActors.clear();
	}
	void Scene::Draw(const class Renderer& renderer) {
		for (const auto& actor : m_actors) {
			actor->Draw(renderer);
		}

	}

	void Scene::UpdateCollisions() {
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB) continue;

				float distance = (actorA->GetTransform().position - actorB->GetTransform().position).Length();
				if (distance <= actorA->GetRadius() * actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}

}