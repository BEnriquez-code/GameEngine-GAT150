#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "Renderer/Texture.h"
#include "Math/Rect.h"

namespace nu {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

<<<<<<< Updated upstream
		void Start()override;
=======
		void Start() override;
>>>>>>> Stashed changes
		void Draw(const Renderer& renderer) override;

		void Read(const json::value_t& value) override;

		void Update(float dt) override;

		const Vector2 GetSize() const { return m_size; }

		bool GetFlipH()const { return m_flipH; }
		void SetFlipH(bool flilpH = true) { m_flipH = flilpH; }
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
	protected:
		std::string m_textureName;
		Rect m_sourceRect;
		Vector2 m_size{ 0.0f, 0.0f };
		bool m_flipH = false;
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
		res_t<Texture> m_texture;
	};
}