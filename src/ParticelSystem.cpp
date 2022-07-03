#include "ParticelSystem.h"

ParticleSystem::ParticleSystem(unsigned int particleCount)
{
	m_particleArray.setPrimitiveType(sf::Quads);
	m_particleArray.resize(particleCount);
	m_particles.resize(particleCount);

	for(std::size_t i = 0; i < particleCount; i += 4)
	{
		m_particleArray[i].texCoords = sf::Vector2f(64,64);
		m_particleArray[i+1].texCoords = sf::Vector2f(64,0);
		m_particleArray[i+2].texCoords = sf::Vector2f(0,0);
		m_particleArray[i+3].texCoords = sf::Vector2f(0,64);
	}

	if(!m_shader.loadFromFile("res\\Shader.fs.txt", sf::Shader::Fragment))
	{
		std::cout << "Error: Unable to load Fragment shader" << std::endl;
	}
}

void ParticleSystem::setTexture(const std::string fileName)
{
	if(!m_texture.loadFromFile(fileName))
		std::cout << "Error: Cant load Texture!" << std::endl;

	m_texture.loadFromFile(fileName);
}

void ParticleSystem::setTexture(const sf::Texture &particleTexture)
{
	m_texture = particleTexture;
}

void ParticleSystem::setEmitter(sf::Vector2f position, float toleranz)
{
	m_emitter = position;
	m_emitterToleranz = toleranz;
	m_emitterRandField = m_emitterToleranz * 2;
}

void ParticleSystem::setEmitter(float x, float y, float toleranz)
{
	m_emitter = sf::Vector2f(x,y);
	m_emitterToleranz = toleranz;
	m_emitterRandField = m_emitterToleranz * 2;
}

void ParticleSystem::setLifeTime(float lifeTime, float toleranz)
{
	m_lifeTime = sf::seconds(lifeTime);
	m_lifeTimeToleranz = toleranz;
	m_lifeTimeRandField = m_lifeTime.asMilliseconds() - (m_lifeTimeToleranz * 1000);
}

void ParticleSystem::setColor(sf::Color color)
{
	for(std::size_t i = 0; i < m_particles.size(); i += 4)
	{
		for(std::size_t j = 0; j < 4; j++)
		{
			m_particleArray[i+j].color = color;
		}
	}
}

void ParticleSystem::setColor(int r, int g, int b, int a)
{
	for(std::size_t i = 0; i < m_particles.size(); i += 4)
	{
		for(std::size_t j = 0; j < 4; j++)
		{
			m_particleArray[i+j].color = sf::Color(r,g,b,a);
		}
	}
}

void ParticleSystem::update(sf::Time elapsedTime)
{
	for (std::size_t i = 0; i < m_particles.size(); i += 4)
	{
		particle& p = m_particles[i];
		p.lifeTime -= elapsedTime;
		
		float ratio = p.lifeTime.asSeconds() / m_lifeTime.asSeconds();

		for(std::size_t j = 0; j < 4; j++)
		{
			m_particleArray[i+j].position += p.velocity * elapsedTime.asSeconds();
			m_particleArray[i+j].position.x += ((m_emitter.x - m_particleArray[i+j].position.x) * ratio) / 100;
            m_particleArray[i+j].color.a = static_cast<sf::Uint8>(ratio * 100);
			m_particleArray[i+j].color.g = ratio * 255;
		}

		if(p.lifeTime < sf::Time::Zero)
		{
			resetParticle(i);
		}
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	
	if(m_texture.getSize() != sf::Vector2u(0,0))
	{
		states.texture = &m_texture;
		states.shader = &m_shader;
	}

	target.draw(m_particleArray, states);
}

void ParticleSystem::resetParticle(std::size_t index)
{
	sf::Vector2f localEmitter;

	if(m_emitterToleranz != 0)
	{
		localEmitter = sf::Vector2f(m_emitter.x + ((std::rand() % m_emitterRandField) - m_emitterToleranz), m_emitter.y);
	}
	else
	{
		localEmitter = m_emitter;
	}

	m_particleArray[index].position = localEmitter + sf::Vector2f(32,32);
	m_particleArray[index+1].position = localEmitter + sf::Vector2f(32,-32);
	m_particleArray[index+2].position = localEmitter + sf::Vector2f(-32,-32);
	m_particleArray[index+3].position = localEmitter + sf::Vector2f(-32,32);

	if(m_lifeTimeToleranz != 0)
	{
		m_particles[index].lifeTime = sf::milliseconds((std::rand() % m_lifeTimeRandField) + (m_lifeTimeToleranz * 1000));
	}
	else
	{
		m_particles[index].lifeTime = m_lifeTime;
	}
	
    float speed = (std::rand() % 50) + 100.f;
    m_particles[index].velocity = sf::Vector2f(0 * speed, -1 * speed);
}




