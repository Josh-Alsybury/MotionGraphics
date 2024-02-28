// platform game.....
// Author :josh a

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h> 
class Game
{
public:
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;


	sf::RectangleShape playerShape;
	

	float velocityX = 0, velocityY = 0, gravity = 0.3;




	static const int numRows = 48;
	static const int numCols = 20;
	int levelData[numRows][numCols] =
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 }, 
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,1,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2 },	
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2 },

	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2 },
	{ 0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,2 },
	{ 0,1,1,1,1,1,1,1,2,0,0,1,0,0,0,0,0,0,0,2 },

	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,2 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2 },
	{ 1,1,4,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2 },

	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2 },
	{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,2 }, 
	{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2 },
	{ 1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2 },
	{ 0,0,1,1,0,3,3,0,0,0,0,0,0,0,5,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,3,3,1,0,0,0,0,0,0,0,2 } 
	};

	sf::RectangleShape level[numRows][numCols];

	bool move = true;
	bool key = false;

	Game()
	{
		window.create(sf::VideoMode(800, 600), "Endless Runner Game");
	}
	void init()
	{
		key = false;
		move = true;
		
		sf::Texture floor;
		floor.loadFromFile("ASSETS\IMAGES\floor.png");

		sf::Texture spike;
		spike.loadFromFile("ASSETS\IMAGES\spike.png");

		sf::Texture key;
		key.loadFromFile("ASSETS\IMAGES\key.png");

		sf::Texture door ;
		door.loadFromFile("ASSETS\IMAGES\door.png");

		sf::Texture jump;
		jump.loadFromFile("ASSETS\IMAGES\jump.png");

		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{

				if (levelData[row][col] == 1)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Red);
 					level[row][col].setTexture(&floor);
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setTexture(&spike);
					level[row][col].setFillColor(sf::Color::Blue);

				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setTexture(&door);
					level[row][col].setFillColor(sf::Color::Green);
				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(70, 100));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setTexture(&key);
					level[row][col].setFillColor(sf::Color::Yellow);
				}
				if (levelData[row][col] == 5)
				{
					level[row][col].setSize(sf::Vector2f(70, 100));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setTexture(&jump);
					level[row][col].setFillColor(sf::Color::Magenta);
				}
				if (levelData[row][col] == 6)
				{
					level[row][col].setSize(sf::Vector2f(40, 40));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setTexture(&key);
					level[row][col].setFillColor(sf::Color::Cyan);
				}
			}
			std::cout << std::endl;
		}

	}
	void run()
	{


		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


		sf::Time timeSinceLastUpdate = sf::Time::Zero;


		sf::Clock clock;

		clock.restart();

		while (window.isOpen())
		{
			if (move == true)
			{

				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}


				timeSinceLastUpdate += clock.restart();


				if (timeSinceLastUpdate > timePerFrame)
				{

					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{

							level[row][col].move(-3.7, 0);
						}

					}


					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
					{
						velocityY = -11.8;
					}

					velocityY = velocityY + gravity;
					playerShape.move(0, velocityY);


					gravity = 0.6;

					for (int row = 0; row < numRows && move == true; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							if (velocityY >= 0)
							{
								if (levelData[row][col] == 1)
								{

									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										if (playerShape.getPosition().y < level[row][col].getPosition().y)
										{
											gravity = 0;
											velocityY = 0;
											playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
											playerShape.move(0, -playerShape.getGlobalBounds().height);
											break;
										}
										else {
											init();
										}
									}
								}
							}
							if (velocityY < 0)
							{
								if (levelData[row][col] == 1)
								{
									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										init();
									}
								}
							}
							if (levelData[row][col] == 2)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
								}
							}
							if (levelData[row][col] == 3)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
									move = false;
								}
							}
							if (levelData[row][col] == 4) 
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()) && key == true)
								{
									level[row][col].setPosition(1000, 1000);
								}
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()) && key == false)
								{
									init();
								}
							}
							if (levelData[row][col] == 5)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									velocityY = -22.8;
								}
							}
							if (levelData[row][col] == 6)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									key = true;
									level[row][col].setPosition(1000, 1000);
								}
							}
						}
					}
					sf::Font m_ArialBlackfont;
					sf::Text m_winText;
					if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
					{
						std::cout << "problem loading arial black font" << std::endl;
					}
					m_winText.setFont(m_ArialBlackfont);
					m_winText.setString("winner");
					m_winText.setStyle(sf::Text::Bold);
					m_winText.setPosition(260.0f, 300.0f);
					m_winText.setCharacterSize(70U);
					m_winText.setOutlineColor(sf::Color::Green);
					m_winText.setFillColor(sf::Color::Red);
					m_winText.setOutlineThickness(3.0f);

					if (playerShape.getPosition().y > 600)
					{
						init();
					}
					window.clear();

					if (move == true)
					{
						for (int row = 0; row < numRows; row++)
						{
							for (int col = 0; col < numCols; col++)
							{
								window.draw(level[row][col]);
								
							}
						}
					}
					window.draw(playerShape);
					if (move == false)
					{
						window.draw(m_winText);
					}
					window.display();

					timeSinceLastUpdate = sf::Time::Zero;
				}
			}
		}
	}
};




int main()
{


	Game game;

		game.init();
		game.run();
	
	return 0;
}
