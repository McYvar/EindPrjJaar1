#include "Game.h"

// Initialse functions
void Game::initWindow(const float& windowWidth, const float& windowHeight)
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight), "Speed racer ofzo");
    this->window->setFramerateLimit(60);
}


// Constructors / Destructors
Game::Game()
    : dt(0),
    sfEvent(),
    window()
{
}


Game::~Game()
{
}


void Game::Start(const float& windowWidth, const float& windowHeight)
{
    this->initWindow(windowWidth, windowHeight);

    // Background stuff
    bgList.push_back(std::make_shared<Background>(Vector2(0, -400), 3000, "background", this->time));

    // Player stuff
    float speed(100.f);
    int lives(3);
    float friction(0.1f);
    std::string playerTexture("playerCar");
    player = std::make_shared<Player>(Vector2(windowWidth / 2, windowHeight * 3 / 4), speed, playerTexture, 0, lives, friction);

    // Obstacles stuff
    this->randomSpawnTime = Math::random(0.5f, 2.f);

    if (!font.loadFromFile("assets/Fascinate-Regular.ttf"))
    {
        std::cout << "Couldn't load font..." << "\n";
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    livesLeft.setFont(font);
    livesLeft.setCharacterSize(24);
    livesLeft.setFillColor(sf::Color::White);
    livesLeft.setStyle(sf::Text::Bold);
    livesLeft.setPosition(Vector2(window->getSize().x - 120, 0).toSFVector2());
    gameOver.setFont(font);
    gameOver.setCharacterSize(64);
    gameOver.setFillColor(sf::Color::Red);
    gameOver.setStyle(sf::Text::Bold);
    gameOver.setPosition(Vector2(this->window->getSize().x * 1 / 6, this->window->getSize().y / 3).toSFVector2());
}


void Game::UpdateDt()
{
    // Update the dt variable with the time it takes to update and render one frame
    this->dt = this->dtClock.restart().asSeconds();
    this->time += this->dt / 100;
    this->resetTime += this->dt;
    if (!isGameOver) this->score += this->dt;
}


// Fucntions
void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}


// Game updates per frame
void Game::update()
{
    this->updateSFMLEvents();

    if (isGameOver) {
        text.setString("Final score: " + std::to_string((int) this->score));
        text.setPosition(Vector2(this->window->getSize().x / 4, this->window->getSize().y * 3 / 5).toSFVector2());
        text.setFillColor(sf::Color::Black);
        gameOver.setString("GAME OVER!");
        return;
    }
    else if (this->player->getLives() <= 0) {
        isGameOver = true;
    }
    
    // Player stuff
    player->UpdateValues(this->window, dt);
    // Background stuff
    if (!bgList.empty()) {
        std::list<std::shared_ptr<Background>> toRemove;
        for (std::list<std::shared_ptr<Background>>::iterator it = bgList.begin(); it != bgList.end(); it++) {
            (*it)->UpdateValues(this->window, this->dt);

            if ((*it)->getPosition().y > -200) {
                bgList.push_back(std::make_shared<Background>(Vector2(0, -400), 3000, "background", this->time));
                toRemove.push_front(*it);
            }
        }

        if (!toRemove.empty()) {
            for (std::list<std::shared_ptr<Background>>::iterator it = toRemove.begin(); it != toRemove.end(); it++) {
                bgList.remove(*it);
            }
        }
        toRemove.clear();
    }

    // Obstacles stuff
    if (this->resetTime > this->randomSpawnTime) {
        resetTime = 0;
        float randomSpeed;
        Vector2 randomDirection;
        Vector2 randomPosition = Vector2(Math::random(90, window->getSize().x -90), -60.f);
        if (this->time * 100 < 6) {
            this->randomSpawnTime = Math::random(3.f, 5.f);
            randomSpeed = Math::random(1000.f, 1400.f);
            float randomX = Math::random(-.1f, .1f);
            randomDirection = Vector2(randomX, 1.f);
        }
        else if (this->time * 100 < 11) {
            this->randomSpawnTime = Math::random(2.5f, 3.5f);
            randomSpeed = Math::random(1300.f, 2000.f);
            float randomX = Math::random(-.2f, .2f);
            randomDirection = Vector2(randomX, 1.f);
        }
        else if (this->time * 100 < 15) {
            this->randomSpawnTime = Math::random(1.3f, 2.f);
            randomSpeed = Math::random(1800.f, 2400.f);
            float randomX = Math::random(-.4f, .4f);
            randomDirection = Vector2(randomX, 1.f);
        }
        else {
            this->randomSpawnTime = Math::random(0.3f, .8f);
            randomSpeed = Math::random(2300.f, 2800.f);
            float randomX = Math::random(-.5f, .5f);
            randomDirection = Vector2(randomX, 1.f);
        }
        obsList.push_back(std::make_shared<Obstacles>(randomPosition, randomSpeed, "enemyCar", this->time, randomDirection));
    }

    if (!obsList.empty()) {
        std::list<std::shared_ptr<Obstacles>> toRemove;
        for (std::list<std::shared_ptr<Obstacles>>::iterator it = obsList.begin(); it != obsList.end(); it++) {
            (*it)->UpdateValues(this->window, this->dt);

            if ((*it)->checkForColission(this->player)) {
                this->player->removeLife();
                toRemove.push_front(*it);
            }

            else if ((*it)->getPosition().y > window->getSize().y) {
                this->score += (*it)->getMovementspeed();
                toRemove.push_front(*it);
            }
        }

        if (!toRemove.empty()) {
            for (std::list<std::shared_ptr<Obstacles>>::iterator it = toRemove.begin(); it != toRemove.end(); it++) {
                obsList.remove(*it);
            }
        }
        toRemove.clear();
    }

    // Text related stuff
    this->text.setString("Score: " + std::to_string((int) this->score));
    this->livesLeft.setString("Lives: " + std::to_string(this->player->getLives()));
}


void Game::render()
{
    this->window->clear(sf::Color(255, 255, 255, 255));

    // Render bg first
    if (!bgList.empty()) {
        for (std::list<std::shared_ptr<Background>>::iterator it = bgList.begin(); it != bgList.end(); it++) {
            (*it)->Render(this->window);
        }
    }

    // then obstacles
    if (!obsList.empty()) {
        for (std::list<std::shared_ptr<Obstacles>>::iterator it = obsList.begin(); it != obsList.end(); it++) {
            (*it)->Render(this->window);
        }
    }

    // then player
    player->Render(this->window);

    // then draw score / lifes
    this->window->draw(text);
    this->window->draw(livesLeft);
    this->window->draw(gameOver);

    this->window->display();
}


void Game::run()
{
    Start(600.f, 600.f);
    while (this->window->isOpen())
    {
        this->UpdateDt();
		this->update();
		this->render();
    }
}
