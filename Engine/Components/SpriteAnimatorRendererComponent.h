#pragma once
#include "SpriteRendererComponent.h"
#include "Resources/ResourceManager.h"

namespace nu {
	class SpriteAnimatorRendererComponent : public SpriteRendererComponent {
<<<<<<< Updated upstream
	
	public:
		CLASS_PROTOTYPE(SpriteAnimatorRendererComponent)

		struct SpriteAnimation {
=======

	public:
		CLASS_PROTOTYPE(SpriteAnimatorRendererComponent)

			struct SpriteAnimation {
>>>>>>> Stashed changes
			std::string name;
			float framesPerSecond{ 10.0f };
			bool loop = true;
			res_t<class TextureFrames> textureFrames;
		};

<<<<<<< Updated upstream
		
=======

>>>>>>> Stashed changes

		void Start() override;
		void Update(float dt) override;

		void Play(const std::string& name);
		bool GetPause() const { return m_pause; }
		void SetPuse(bool pause = true) { m_pause = pause; }

		void Read(const json::value_t& value) override;

	private:
		unsigned int m_frame = 0;
		float m_frameTimer = 0;
		bool m_pause = false;
		std::string m_defaultAnimationName;

		SpriteAnimation m_spriteAnimation;
		std::map<std::string, SpriteAnimation> m_spriteAnimations;
	};
}