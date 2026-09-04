#pragma once
<<<<<<< Updated upstream
#include "Components/ColliderComponent.h"
=======
#include "ColliderComponent.h"
>>>>>>> Stashed changes

namespace nu {

	class CircleColliderComponent : public ColliderComponent {
	public:
		CLASS_PROTOTYPE(CircleColliderComponent)

		void Read(const json::value_t& value) override;

		float GetRadius() const { return m_radius; }
	protected:
		float m_radius;
		bool CheckCollision(const ColliderComponent& other);
	};
}