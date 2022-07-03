#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "ParticelSystem.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Particles");
	window.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("res\\Fackel.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(370,470);

	ParticleSystem particles(2500);
	particles.setTexture("res\\fire.png");
	particles.setEmitter(sf::Vector2f(500,500), 70);
	particles.setLifeTime(3,1);
	particles.setColor(sf::Color(255,170,3,50));
	
	sf::Clock clock;

	int angel = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

		sf::Time elapsedTime = clock.restart();
		particles.update(elapsedTime);

		window.clear();

		window.draw(sprite);
		window.draw(particles);

		window.display();
    }

    return 0;
}