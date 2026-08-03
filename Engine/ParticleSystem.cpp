#include "pch.h"
#include "ParticleSystem.h"
#include "Renderer.h"
namespace nu {

	bool ParticleSystem::Initialize(size_t size){
		// reserve # particles in container
		m_particles.resize(size);

		return true;
	}

	void ParticleSystem::Shutdown(){
		m_particles.clear();
		// clear all particles
		// TODO: clear() particles
	}

	void ParticleSystem::Update(float dt)
	{
		// update active particles
		for (auto& particle : m_particles)
		{
			if (!particle.active/*TODO: particle is not active */) continue;

			
			// reduce particle.lifespan by subtracting delta time
			// TODO: particle.lifespan -= delta time
			particle.lifespan -= dt;
			// set active if (particle.lifespan > 0);
			// TODO: particle.active = particle lifespan > 0
			if (particle.lifespan > 0) {
				particle.active = (particle.lifespan > 0.0f);
			}

			// update position with velocity (multiply by dt)
			// TODO: update position += with particle velocity * delta time
			particle.position += particle.velocity * (dt * 0.09f);
		}
	}

	void ParticleSystem::Draw(const Renderer& renderer)
	{
		// draw all active particlee
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				renderer.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				renderer.DrawPoint(particle.position.x, particle.position.y);
				// set particle color and draw point at current position
				// TODO: set color with particle color
				// TODO: draw point with particle position

				
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle)
	{
		// get free particle
		Particle* freeParticle = GetFreeParticle();
		// check if free particle is not nullptr
		if (freeParticle)
		{
			// set free particle object with particle
			// TODO: dereference (*) free particle and set it to particle
			// set particle active
			// TODO: set free particle active to true

			*freeParticle = particle;
			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		// find and return inactive particle 
		for (auto& particle : m_particles)
		{
			// return pointer to inactive particle
			//if (/*TODO: particle is inactive)*/
				//return /*address (&) of particle*/

			if (!particle.active) {
				return &particle;
			}
		}

		// no free particles, return nullptr
		return nullptr;
	}

}