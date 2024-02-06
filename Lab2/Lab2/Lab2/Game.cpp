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
	setup();
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
	if (sf::Keyboard::Left == t_event.key.code)
	{
		moveLeft();
	}
	if (sf::Keyboard::Right == t_event.key.code)
	{
		moveRight();
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
	Player();

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_player);

	for (int i = 0; i < numWalls; i++)
	{
		m_window.draw(walls[i]);
	}

	m_window.display();
}

void Game::Player()
{
	m_player.setFillColor(sf::Color::Yellow);
	m_player.setPosition(playerX,500);
	m_player.setSize(sf::Vector2f(25, 25));
}

void Game::moveLeft()
{
	playerX = playerX - Velocity;
	m_player.setPosition(playerX, 500);
}

void Game::moveRight()
{
	playerX = playerX + Velocity;
	m_player.setPosition(playerX, 500);
}

void Game::setup()
{
int levelData[] = {
1,1,1,1,1,0,1,1,1,1,
1,1,1,1,1,0,0,0,0,1,
1,1,1,1,0,0,0,1,0,1,
1,1,0,0,0,0,0,1,0,1,
1,0,0,1,1,0,0,0,0,1,
1,0,0,1,1,0,0,1,1,1,
1,1,0,0,1,0,1,1,1,1,
1,1,1,0,0,0,1,1,1,1,
1,1,0,0,0,0,0,1,1,1};


 for (int i = 0; i < numWalls; i++)
 {
	 walls[i].setPosition(wallsX, wallsY);
	 walls[i].setSize(sf::Vector2f(90,60));

	 if(levelData[i] == 1)
	 { 
		 walls[i].setFillColor(sf::Color::Red);
	 }

	 if (levelData[i] == 0)
	 {
		 walls[i].setFillColor(sf::Color::Black);
	 }
	 wallsX = wallsX + 90;

	 if (wallsX >= 810)
	 {
		 wallsY + 60;
		 wallsX = 0;
	 }
	 walls[i].setPosition(wallsX, wallsY);
 }

}




