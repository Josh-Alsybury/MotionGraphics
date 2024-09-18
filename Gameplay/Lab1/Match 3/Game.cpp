#include "Game.h"
#include <iostream>
#include <ctime>

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 510U, 510U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	wallsetup();
	blockSetup();
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
	mousePoint();
	match();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear();



	for (int WallType = 0; WallType < NUM_WALLS; WallType++)
	{
		m_window.draw(Walls[WallType]);
	}
	for (int i = 0; i < FRUIT; i++)
	{
		m_window.draw(fruits[i]);
	}
	m_window.draw(mPoint);
	m_window.display();
}

void Game::wallsetup()
{
	for (int i = 0; i < NUM_WALLS; i++)
	{
		Walls[i].setPosition(sf::Vector2f(0,50*i));
		Walls[i].setSize(sf::Vector2f(800,10));
		Walls[i].setOutlineColor(sf::Color::Red);
		Walls[i].setOutlineThickness(0.5f);
		Walls[i].setFillColor(sf::Color::Red);

		sf::Vector2f WallPos = Walls[i].getPosition();

		if (WallPos.y >= 775)
		{
			Walls[i].setPosition(sf::Vector2f( 50*(i - 20),0));
			Walls[i].setSize(sf::Vector2f(10,800));
		}
	}
}

void Game::blockSetup()
{
	srand(time(0));
	for (int i = 0;i < FRUIT; i++)
	{
		int randomNum = rand() % 4 + 1;

		fruits[i].setSize(sf::Vector2f(40, 40));
		fruits[i].setOutlineThickness(2.0f);
		fruits[i].setFillColor(sf::Color::Blue);

		fruits[i].setPosition(blockx, blocky);

		blockx += 50;

		if (blockx > 460)
		{
			blockx = 10;
			blocky += 50;
		}
		if (randomNum == 3)
		{
			fruits[i].setFillColor(sf::Color::Green);
		}
		if (randomNum == 2)
		{
			fruits[i].setFillColor(sf::Color::Cyan);
		}
		if (randomNum == 1)
		{
			fruits[i].setFillColor(sf::Color::Magenta);
		}
       
	}
}

void Game::mousePoint()
{
	sf::Vector2i mPosition = sf::Mouse::getPosition(m_window);

	mPoint.setFillColor(sf::Color::White);
	mPoint.setRadius(4.0f);
	mPoint.setPosition(mPosition.x, mPosition.y);
}

void Game::match()
{
	for (int i = 0; i < FRUIT; i++)
	{

		if (mPoint.getGlobalBounds().intersects(fruits[i].getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (fruits[i].getFillColor() == sf::Color::Blue)
			{
				fruits[i].setOutlineColor(sf::Color::Black);
				colour1.setFillColor(fruits[i].getFillColor());
				std::cout << "Blue" << std::endl;
			}
			if (fruits[i].getFillColor() == sf::Color::Green)
			{
				colour1.setFillColor(fruits[i].getFillColor());
				std::cout << "Green" << std::endl;
			}
			if (fruits[i].getFillColor() == sf::Color::Cyan)
			{
				colour1.setFillColor(fruits[i].getFillColor());
				std::cout << "Cyan" << std::endl;
			}
			if (fruits[i].getFillColor() == sf::Color::Magenta)
			{
				colour1.setFillColor(fruits[i].getFillColor());
				std::cout << "Magenta" << std::endl;
			}
		}
		if (mPoint.getGlobalBounds().intersects(fruits[i].getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (fruits[i].getFillColor() == sf::Color::Blue)
			{
				fruits[i].setOutlineColor(sf::Color::Transparent);
				colour2.setFillColor(fruits[i].getFillColor());
				std::cout << "Blue" << std::endl;
			}
			if (fruits[i].getFillColor() == sf::Color::Green)
			{
				colour2.setFillColor(fruits[i].getFillColor());
				std::cout << "Green" << std::endl;
			}
			if (fruits[i].getFillColor() == sf::Color::Cyan)
			{
				colour2.setFillColor(fruits[i].getFillColor());
				std::cout << "Cyan" << std::endl;
			}
			if (fruits[i].getFillColor() == sf::Color::Magenta)
			{
				colour2.setFillColor(fruits[i].getFillColor());
				std::cout << "Magenta" << std::endl;
			}
			
		}
		if (colour1.getFillColor() != colour2.getFillColor())
		{
			std::cout << "can swap" << std::endl;
			
		}
	}
	

}



