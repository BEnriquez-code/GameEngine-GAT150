#pragma once
#include "RendererComponent.h"
#include "Resource.h"
#include "Texture.h"
namespace nu {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)
		void Draw(const Renderer& renderer) override;

		void Read(const json::value_t& value) override;

		void Update(float dt) override;
	protected:
		res_t<Texture> m_texture;
	};
}