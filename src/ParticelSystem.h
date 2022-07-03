#include <SFML\Graphics.hpp>
#include <iostream>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{

public:
	ParticleSystem(unsigned int particleCount);
	void setTexture(const std::string fileName);
	void setTexture(const sf::Texture &particleTexture);
	void setEmitter(sf::Vector2f position, float toleranz = 0);
	void setEmitter(float x, float y, float toleranz = 0);
	void setLifeTime(float lifeTime = 4, float toleranz = 0);
	void setColor(sf::Color color = sf::Color(255,255,255,255));
	void setColor(int r = 255, int g = 255, int b = 255, int a = 255);
	void update(sf::Time elapsedTime);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void resetParticle(std::size_t index);

	struct particle
	{
		sf::Vector2f velocity;
		sf::Time lifeTime;
	};

	std::vector<particle> m_particles;
	sf::VertexArray m_particleArray;
	
	sf::Vector2f m_emitter;
	float m_emitterToleranz;
	int m_emitterRandField;
	
	sf::Time m_lifeTime;
	float m_lifeTimeToleranz;
	int m_lifeTimeRandField;
	
	sf::Texture m_texture;
	
	sf::Shader m_shader;
};

