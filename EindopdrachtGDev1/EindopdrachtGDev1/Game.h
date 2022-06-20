#pragma once

#include "Player.h"
#include "Background.h"
#include "Obstacles.h"
#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>

class Game
{
private:
	// Variables
	std::shared_ptr<Player> player;
	std::list<std::shared_ptr<Background>> bgList;
	std::list<std::shared_ptr<Obstacles>> obsList;

	std::shared_ptr<sf::RenderWindow> window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float time = 0;
	float resetTime = 0;
	float randomSpawnTime = 0;
	float dt = 0;

	sf::Font font;
	sf::Text text;
	float score = 0;
	sf::Text livesLeft;
	sf::Text gameOver;

	bool isGameOver = false;

	// Initialisation
	void initWindow(const float& windowWidth, const float& windowHeight);

public:
	// Constructors / Destructors
	Game();
	~Game();

	// Functions
	void Start(const float& windowWidth, const float& windowHeight);
	void UpdateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};