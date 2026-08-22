#pragma once
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MathUtils.h"
#include "Transform.h"
#include <fmod.hpp>
#include "StringUtils.h"

#include "Factory.h"

#include "Text.h"


// systems
#include "File.h"
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "Audio.h"
#include "ParticleSystem.h"
#include "Texture.h"
#include "Json.h"
#include "Physics.h"


//framework
#include "Game.h"
#include "Actor.h"
#include "Scene.h"

namespace nu {
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; };

		bool Initialize();
		void Shutdown();
		void Update();

		Input& GetInput() { return m_input; };
		Renderer& GetRenderer() { return m_renderer; };
		Audio& GetAudio() { return m_audio; };
		Time& GetTime() { return m_time; };
		Physics& GetPhysics() { return m_physics; }

		ParticleSystem& GetPS() { return m_particleSystem; }

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		

	private:
		Engine() = default;

		Input m_input;
		Renderer m_renderer;
		Audio m_audio;
		Physics m_physics;

		Time m_time;
		ParticleSystem m_particleSystem;
	};
}