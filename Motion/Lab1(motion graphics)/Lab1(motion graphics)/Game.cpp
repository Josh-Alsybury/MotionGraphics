/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	Walls();
	Player();
	Enemy();
	Move();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Up == t_event.key.code)
	{
		if (direction == false)
		{
			direction = true;
		}
    	else if (direction == true)
		{ 
			direction = false;
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	Move();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_window.draw(m_wall);
	m_window.draw(m_wall2);
	m_window.draw(m_stripe);
	m_window.draw(m_stripe2);
	m_window.draw(m_player);
	m_window.draw(m_Enemy);

	m_window.display();
}

void Game::Walls()
{
	m_wall.setFillColor(sf::Color::Blue);
	m_wall.setPosition(0, 300);
	m_wall.setSize(sf::Vector2f(800,50));

	m_wall2.setFillColor(sf::Color::Blue);
	m_wall2.setPosition(0, 440);
	m_wall2.setSize(sf::Vector2f(800, 50));

	m_stripe.setFillColor(sf::Color::Black);
	m_stripe.setPosition(0, 315.8);
	m_stripe.setSize(sf::Vector2f(800, 20));

	m_stripe2.setFillColor(sf::Color::Black);
	m_stripe2.setPosition(0, 455.8);
	m_stripe2.setSize(sf::Vector2f(800, 20));
}

void Game::Player()
{
	m_player.setFillColor(sf::Color::Yellow);
	m_player.setPosition(playerX, 370);
	m_player.setSize(sf::Vector2f(50, 50));
}

void Game::Enemy()
{
	m_Enemy.setFillColor(sf::Color::Red);
	m_Enemy.setPosition(enemyX, 370);
	m_Enemy.setSize(sf::Vector2f(50, 50));
}

void Game::Move()
{
	if (direction == false)
	{
		playerX = playerX + Velocity;
		m_player.setPosition(playerX, 370);
	}
	if (direction == true)
	{
		playerX = playerX - Velocity;
		m_player.setPosition(playerX, 370);
	}

	if(playerX < enemyX)
	{
		enemyX = enemyX - Velocity;
		m_Enemy.setPosition(enemyX, 370);
	}
	if (playerX > enemyX)
	{
		enemyX = enemyX + Velocity;
		m_Enemy.setPosition(enemyX, 370);
	}


	if (playerX > 801)
	{
		playerX = 10;
	}
	if (playerX < 5)
	{
		playerX = 800;
	}
}
