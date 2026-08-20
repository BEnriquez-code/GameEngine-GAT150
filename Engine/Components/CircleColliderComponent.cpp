#include "pch.h"
#include "CircleColliderComponent.h"
#include "Factory.h"
#include "Actor.h"

#include <iostream>

namespace nu {
    FACTORY_REGISTER(CircleColliderComponent)

    bool CircleColliderComponent::CheckCollision(const ColliderComponent& other){

        const CircleColliderComponent* otherCircle = dynamic_cast<const CircleColliderComponent*>(&other);
        if (!otherCircle) {
            std::cerr << "Could not cast :" << otherCircle << ", as CircleColliderComponent" << std::endl;
            return false;
        }

        float distance = GetOwner()->GetTransform().position.Distance(other.GetOwner()->GetTransform().position);
        float radius = m_radius + otherCircle->GetRadius();
        
        return distance <= radius;
    }
    void CircleColliderComponent::Read(const json::value_t& value){
        ColliderComponent::Read(value);
        JSON_READ_NAME(value, "radius", m_radius);
    }
}
