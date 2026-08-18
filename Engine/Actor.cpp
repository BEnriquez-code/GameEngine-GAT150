#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "Texture.h"
#include "MathUtils.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "Components/RendererComponent.h"

namespace nu {
    FACTORY_REGISTER(Actor)

    void Actor::Update(float dt) {

        //physics
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.9997f; // Apply friction to slow down the actor over time

        m_transform.position.x = math::Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = math::Wrap(0.0f, 1024.0f, m_transform.position.y);

        for (auto component : m_components) {
            component->Update(dt);
        }

    }
    void Actor::Draw(const Renderer& render) const {

        for (auto component : m_components) {
            auto rendererComponent = dynamic_cast<RendererComponent*>(component);
            if (rendererComponent) {
               rendererComponent->Draw(render);
            }
            
        }
    }

    float Actor::GetRadius() const {
   

	   return 0.0f;
    }

    void Actor::Read(const json::value_t& value) {
        Object::Read(value);

        if (JSON_HAS_NAME(value, "transform")) {
            m_transform.Read(JSON_GET_NAME(value, "transform"));
        }

        JSON_READ_NAME(value, "name", m_name);
        JSON_READ_NAME(value, "tag", m_tag);
        
        JSON_READ_OPTIONAL(value, "velocity", m_velocity);
        JSON_READ_OPTIONAL(value, "damping", m_damping);

        //read actor components
        if (JSON_HAS_NAME(value, "components")) {
            for (auto& componentValue : JSON_GET_NAME(value, "component").GetArray()) {


                std::string typeName;
                JSON_READ_NAME(componentValue, "type", typeName);

                auto component = Factory::Instance().Create<Component>(typeName);

                if (component) {
                    component->Read(componentValue);
                }
            }
        }

    }

}