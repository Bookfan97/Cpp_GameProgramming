#include "ParticleSystem.h"

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_Vertices, states);
}

void ParticleSystem::init(int numParticles)
{
	m_Vertices.setPrimitiveType(Points);
	m_Vertices.resize(numParticles);
	for (int i = 0; i < numParticles; i++)
	{
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.f;
		float speed = (rand() % 600) + 600.f;
		Vector2f direction;
		direction = Vector2f(cos(angle) * speed, sin(angle) * speed);
		m_Particles.push_back(Particle(direction));
	}
}

void ParticleSystem::emitParticles(Vector2f startPosition)
{
	m_IsRunning = true;
	m_Duration = 2;
	vector<Particle>::iterator i;
	int currentVertex = 0;
	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		m_Vertices[currentVertex].color = Color::Yellow;
		(*i).setPosition(startPosition);
		currentVertex++;
	}
}

void ParticleSystem::update(float elapsed)
{
	m_Duration -= elapsed;
	vector<Particle>::iterator i;
	int currentVertex = 0;
	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		(*i).update(elapsed);
		m_Vertices[currentVertex].position = (*i).getPosition();
		currentVertex++;
	}

	if (m_Duration < 0)
	{
		m_IsRunning = false;
	}
}

bool ParticleSystem::running()
{
	return m_IsRunning;
}