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
	bullet();
	setup();
	setupFontAndText();
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
	if (sf::Keyboard::Space == t_event.key.code)
	{
		move = true;
	}
	if (sf::Keyboard::X == t_event.key.code)
	{
		firing = true;
	}
	if (sf::Keyboard::R == t_event.key.code)
	{
		
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
	if (move == true && endGame == false && win == false)
	{
		for (int i = 0; i < numWalls; i++)
		{
			walls[i].setPosition(walls[i].getPosition().x, walls[i].getPosition().y + 1);
		}
	}
	if (walls[numWalls - 1].getPosition().y > 3600)
	{
		win = true;
	}
	m_score.setString("score :" + std::to_string(score));

	Player();
	fire();
	collision();
}


/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	for (int i = 0; i < numWalls; i++)
	{
		m_window.draw(walls[i]);
	}
	if(move == false)
	{
		m_window.draw(m_welcomeMessage);
	}
	if(endGame == true)
	{
		m_window.draw(m_endText);
	}
	if (win == true)
	{
		m_window.draw(m_winText);
	}
	
	m_window.draw(m_score);
	
	m_window.draw(m_bullet);

	m_window.draw(m_player);

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
	if (endGame == false && win == false && move == true)
	{
		playerX = playerX - Velocity;
		m_player.setPosition(playerX, 500);
	}
}

void Game::moveRight()
{
	if (endGame == false && win == false && move == true)
	{
		playerX = playerX + Velocity;
		m_player.setPosition(playerX, 500);
	}
}

void Game::setup()
{
int levelData[] = {
1,1,1,1,1,3,1,1,0,1,
1,1,1,1,0,0,0,0,0,1,
1,1,1,1,0,0,2,0,1,1,
1,1,1,1,0,0,0,1,1,1,
1,1,1,1,0,2,0,1,1,1,
1,1,1,1,0,3,0,1,1,1,
1,1,1,1,0,0,1,1,1,1,
1,1,1,0,2,0,1,1,1,1,
1,1,0,0,0,0,0,1,1,1,

1,1,1,1,0,1,0,1,1,1,
1,1,1,1,0,2,0,1,1,1,
1,1,1,1,1,0,0,1,1,1,
1,1,1,1,0,0,0,1,1,1,
1,1,1,1,2,1,1,1,1,1,
1,1,1,1,3,0,0,1,1,1,
1,1,1,1,0,0,1,1,1,1,
1,1,1,0,0,2,1,1,1,1,
1,1,0,0,0,0,0,1,1,1,

1,1,0,0,0,0,1,1,1,1,
1,1,1,0,2,3,0,1,1,1,
1,1,1,0,0,1,1,1,1,1,
1,1,1,1,2,0,1,1,1,1,
1,1,1,1,0,0,0,1,1,1,
1,1,1,1,1,0,1,1,1,1,
1,1,1,1,1,2,1,1,1,1,
1,1,1,0,0,3,1,1,1,1,
1,1,0,1,2,0,1,1,1,1, 
1,1,0,0,0,0,1,1,1,1,

1,1,0,3,1,1,1,1,1,1,
1,1,0,0,1,1,1,1,1,1,
1,1,0,2,0,0,1,1,1,1,
1,1,1,0,0,0,3,1,1,1,
1,1,1,1,0,1,0,1,1,1,
1,1,1,1,3,1,0,1,1,1,
1,1,1,1,0,1,0,1,1,1,
1,1,1,1,0,0,2,1,1,1,
1,1,1,1,0,0,0,1,1,1,
1,1,1,1,0,0,0,0,1,1, 

1,1,1,1,1,2,0,0,1,1,
1,1,1,1,1,3,1,0,1,1,
1,1,1,1,1,0,0,0,1,1,
1,1,1,1,1,1,3,1,1,1,
1,1,1,1,1,1,0,1,1,1,
1,1,1,1,2,0,2,1,1,1,
1,1,1,1,0,1,0,1,1,1,
1,1,1,1,0,0,0,1,1,1,
0,0,0,0,0,0,0,0,1,1,
0,0,0,0,0,0,0,0,1,0};


 for (int i = 0; i < numWalls; i++)
 {
	 walls[i].setPosition(wallsX, wallsY);
	 walls[i].setSize(sf::Vector2f(90,60));

	 if (levelData[i] == 3)
	 {
		 walls[i].setFillColor(sf::Color::Yellow);
	 }
	 if (levelData[i] == 2)
	 {
		 walls[i].setFillColor(sf::Color::Magenta);
		 walls[i].setSize(sf::Vector2f(20, 20));
		 walls[i].setOrigin(-30, -30);
	 }
	 if(levelData[i] == 1)
	 { 
		 walls[i].setFillColor(sf::Color::Red); 
	 }
	 if (levelData[i] == 0)
	 {
		 walls[i].setFillColor(sf::Color::Black);
	 }
	 wallsX = wallsX + 90;

     if (wallsX >= 820)
	 {
		 wallsY = wallsY+ 60;
		 wallsX = 0;

		 walls[i].setPosition(wallsX, wallsY);
	 }
 }
}

void Game::bullet()
{
	m_bullet.setFillColor(sf::Color::Green);
	m_bullet.setPosition(playerX, bulletY);
	m_bullet.setSize(sf::Vector2f(10, 10));
}

void Game::fire()
{
	if (firing == true )
	{
		bulletY = bulletY - Velocity;
	}
	if (bulletY < distance)
	{
		firing = false;
		bulletY = playerY;
	}
	m_bullet.setPosition(playerX, bulletY);
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("PRESS SPACE TO START");
	m_welcomeMessage.setStyle(sf::Text::Bold);
	m_welcomeMessage.setPosition(130.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(40U);
	m_welcomeMessage.setOutlineColor(sf::Color::Green);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

	m_endText.setFont(m_ArialBlackfont);
	m_endText.setString("YOU LOSE");
	m_endText.setStyle(sf::Text::Bold);
	m_endText.setPosition(160.0f, 40.0f);
	m_endText.setCharacterSize(40U);
	m_endText.setOutlineColor(sf::Color::Green);
	m_endText.setFillColor(sf::Color::Black);
	m_endText.setOutlineThickness(3.0f);

	m_winText.setFont(m_ArialBlackfont);
	m_winText.setString("winner");
	m_winText.setStyle(sf::Text::Bold);
	m_winText.setPosition(260.0f, 300.0f);
	m_winText.setCharacterSize(70U);
	m_winText.setOutlineColor(sf::Color::Green);
	m_winText.setFillColor(sf::Color::Black);
	m_winText.setOutlineThickness(3.0f);

	m_score.setFont(m_ArialBlackfont);
	m_score.setString("score :" + std::to_string(score));
	m_score.setStyle(sf::Text::Bold);
	m_score.setPosition(10.0f, 10.0f);
	m_score.setCharacterSize(20U);
	m_score.setOutlineColor(sf::Color::Green);
	m_score.setFillColor(sf::Color::Black);
	m_score.setOutlineThickness(3.0f);
}

void Game::collision()
{
	for (int i = 0; i < numWalls; i++)
	{
		if (walls[i].getGlobalBounds().intersects(m_player.getGlobalBounds()))
		{
			if (walls[i].getFillColor() ==sf::Color::Red || walls[i].getFillColor() == sf::Color::Yellow)
			{
				endGame = true;
			}
		}
		if (walls[i].getGlobalBounds().intersects(m_player.getGlobalBounds())|| walls[i].getGlobalBounds().intersects(m_bullet.getGlobalBounds()))
		{
			if (walls[i].getFillColor() == sf::Color::Magenta)
			{
				score++;
				walls[i].setPosition(-1000, -1000);
			}
		}
		if (walls[i].getGlobalBounds().intersects(m_bullet.getGlobalBounds()))
		{
			if (walls[i].getFillColor() == sf::Color::Yellow)
			{
				score++;
				walls[i].setPosition(-1000, -1000);
			}
		}
	}
}




