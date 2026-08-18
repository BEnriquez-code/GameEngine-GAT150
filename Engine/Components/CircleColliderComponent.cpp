#include "pch.h"
#include "CircleColliderComponent.h"
#include "Factory.h"
#include "Actor.h"

namespace nu {
    FACTORY_REGISTER(CircleColliderComponent)

    bool CircleColliderComponent::CheckCollision(const ColliderComponent& other){

        float distance = GetOwner()->GetTransform().position.Distance(other.GetOwner()->GetTransform().position);
        
        return false;
    }
    void CircleColliderComponent::Read(const json::value_t& value){
        ColliderComponent::Read(value);
        JSON_READ_NAME(value, "radius", m_radius);
    }
}
