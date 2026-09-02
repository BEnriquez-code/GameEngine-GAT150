#pragma once
<<<<<<< Updated upstream
#include "Components/Component.h"
namespace nu{
=======
#include "Component.h"
namespace nu {
>>>>>>> Stashed changes
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(const ColliderComponent& other) = 0;
	};
}