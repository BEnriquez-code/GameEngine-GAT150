#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "Texture.h"
#include "MathUtils.h"

namespace nu {
    void Actor::Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.9997f; // Apply friction to slow down the actor over time

        m_transform.position.x = math::Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = math::Wrap(0.0f, 1024.0f, m_transform.position.y);

    }
    void Actor::Draw(const Renderer& render) const {
        if (m_model) {
            render.DrawModel(*m_model, m_transform);
        }

        else if (m_texture) {
            render.DrawTexture(*m_texture, m_transform.position.x, 
                m_transform.position.y, m_transform.rotation, m_transform.scale);
        }
    }

    float Actor::GetRadius() const {
       if (m_model)return m_model->GetRadius() * m_transform.scale * 0.25f;

	   if (m_texture) return (m_texture->GetSize().Length() * 0.25f ) *0.25f;

	   return 0.0f;
    }   

}