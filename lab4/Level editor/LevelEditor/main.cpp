// level editor
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
enum class GameState
{
	Menu,
	Gameplay,
	Editor
};

struct Button
{
	sf::Text text;
	sf::RectangleShape rectangle;
};

class Game
{
public:
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;

	sf::Font font;

	sf::RectangleShape playerShape;

	sf::RectangleShape tilePallet[6];
	int selectedTile = 0;

	Button buttons[3];

	sf::CircleShape cursor;

	GameState m_currentGamestate = GameState::Menu;

	float velocityX = 0, velocityY = 0, gravity = 0.3;

	static const int numRows = 18;
	static const int numCols = 45;
	int levelData[numRows][numCols] =
	{
		
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,2,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,1,1,2,2,1,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	sf::RectangleShape level[numRows][numCols];

	bool move = true;
	bool key1 = false;

	Game()
	{
		window.create(sf::VideoMode(800, 600), "Level Editor");
	}

	void init()
	{
		key1 = false;
		move = true;

		if (!font.loadFromFile("ASSETS/FONTS/ariblk.ttf"))
		{
			std::cout << "Error loading font." << std::endl;
		}

		//Menu Buttons
		for (int i = 0; i < 3; i++)
		{
			//Rectangle
			buttons[i].rectangle.setSize(sf::Vector2f(200.0f, 50.0f));
			buttons[i].rectangle.setOrigin(100.0f, 25.0f);
			buttons[i].rectangle.setFillColor(sf::Color::White);
			buttons[i].rectangle.setPosition(400.0f, 150.0f + 150.0f * i);

			//Text
			buttons[i].text.setFont(font);
			buttons[i].text.setCharacterSize(24.0f);
			buttons[i].text.setFillColor(sf::Color::White);
			buttons[i].text.setOutlineThickness(2.0f);
			buttons[i].text.setOutlineColor(sf::Color::Black);

			if (i == 0)
			{
				buttons[i].text.setString("Play");
			}
			else if (i == 1)
			{
				buttons[i].text.setString("Edit Level");
			}
			else if (i == 2)
			{
				buttons[i].text.setString("Exit");
			}

			buttons[i].text.setOrigin(buttons[i].text.getGlobalBounds().width / 2.0f, buttons[i].text.getGlobalBounds().height / 2.0f);
			buttons[i].text.setPosition(400.0f, 150.0f + 150.0f * i);
		}

		for (int i = 0; i < 6; i++)
		{
			tilePallet[i].setPosition(sf::Vector2f(i * 70, 0));
			tilePallet[i].setSize(sf::Vector2f(70, 30));
			tilePallet[i].setOutlineColor(sf::Color::Transparent);
			tilePallet[i].setOutlineThickness(2.0f);

			if (i == 0)
			{
				tilePallet[i].setFillColor(sf::Color::Transparent);
			}
			else if (i == 1)
			{
				tilePallet[i].setFillColor(sf::Color::Blue);
			}
			else if (i == 2)
			{
				tilePallet[i].setFillColor(sf::Color::Red);
			}
			else if (i == 3)
			{
				tilePallet[i].setFillColor(sf::Color::Green);
			}
			else if (i == 4)
			{
				tilePallet[i].setFillColor(sf::Color::Magenta);
			}
			else if (i == 5)
			{
				tilePallet[i].setFillColor(sf::Color::Cyan);
			}
			else if (i == 6)
			{
				tilePallet[i].setFillColor(sf::Color::Yellow);
			}
		}

		cursor.setRadius(2.0f);
		cursor.setOrigin(2.0f, 2.0f);
		cursor.setFillColor(sf::Color::Red);
		cursor.setPosition(100.0f, 100.0f);

		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				level[row][col].setSize(sf::Vector2f(70, 30));
				level[row][col].setPosition(col * 70, 60 + row * 30);
				level[row][col].setOutlineThickness(2.0f);
				level[row][col].setFillColor(sf::Color::Transparent);

				if (levelData[row][col] == 1)
				{
					level[row][col].setFillColor(sf::Color::Blue);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setFillColor(sf::Color::Red);
				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setFillColor(sf::Color::Green);
				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setFillColor(sf::Color::Magenta);
				}
				if (levelData[row][col] == 5)
				{
					level[row][col].setFillColor(sf::Color::Cyan);
				}
				if (levelData[row][col] == 6)
				{
					level[row][col].setFillColor(sf::Color::Yellow);
				}
			}
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
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			timeSinceLastUpdate += clock.restart();

			if (timeSinceLastUpdate > timePerFrame)
			{
				switch (m_currentGamestate)
				{
				case GameState::Menu:
					updateMenu();
					renderMenu();
					break;
				case GameState::Gameplay:
					updateGameplay();
					renderGameplay();
					break;
				case GameState::Editor:
					updateEditor();
					renderEditor();
					break;
				default:
					break;
				}

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}

	void updateGameplay()
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			switch (0) {
			case 0: // Play button
				m_currentGamestate = GameState::Menu;
				break;
			default:
				break;
			}
			init();
		}

		velocityY = velocityY + gravity;
		playerShape.move(0, velocityY);

		gravity = 0.6;

		for (int row = 0; row < numRows; row++)
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
						switch (0) {
						case 0: // Play button
							m_currentGamestate = GameState::Menu;
							break;
						default:
							break;
						}
						init();
					}
				}
				if (levelData[row][col] == 4)
				{
					if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()) && key1 == true)
					{
						level[row][col].setPosition(1000, 1000);
					}
					if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()) && key1 == false)
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
						key1 = true;
						level[row][col].setPosition(1000, 1000);
					}
				}

				if (playerShape.getPosition().y > 600)
				{
					init();
				}
			}
		}
		if (playerShape.getPosition().y > 600)
		{
			init();
		}
	}

	void renderGameplay()
	{
		window.clear();

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				level[row][col].setOutlineColor(sf::Color::Transparent);
				window.draw(level[row][col]);
			}
		}
		window.draw(playerShape);

		window.display();
	}

	void updateMenu() // updates the menu
	{
		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		for (size_t i = 0; i < 3; i++) {
			if (cursor.getGlobalBounds().intersects(buttons[i].rectangle.getGlobalBounds())) {
				buttons[i].rectangle.setScale(1.1f, 1.1f);
				buttons[i].text.setScale(1.1f, 1.1f);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					switch (i) {
					case 0: // Play button
						m_currentGamestate = GameState::Gameplay;
						break;
					case 1: // Edit Level button
						m_currentGamestate = GameState::Editor;
						break;
					case 2: // Exit button
						window.close();
						break;
					default:
						break;
					}
				}
			}
			else {
				buttons[i].rectangle.setScale(1.0f, 1.0f);
				buttons[i].text.setScale(1.0f, 1.0f);
			}
		}
	}

	void renderMenu() // renders the menu
	{
		window.clear();

		for (auto& button : buttons)
		{
			window.draw(button.rectangle);
			window.draw(button.text);
		}

		window.draw(cursor);

		window.display();
	}

	void updateEditor()
	{
		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		
			for (size_t i = 0; i < 6; i++) {
				if (cursor.getGlobalBounds().intersects(tilePallet[i].getGlobalBounds())) {
					tilePallet[i].setOutlineColor(sf::Color::Green);
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							selectedTile = i;
						}
					}
				}
				else
				{
					tilePallet[i].setOutlineColor(sf::Color::White);
				}
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (cursor.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
						{
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								levelData[row][col] = selectedTile;
							}
						}
						switch (levelData[row][col])
						{
						case 0:
							level[row][col].setFillColor(sf::Color::Transparent);
							break;
						case 1:
							level[row][col].setFillColor(sf::Color::Blue);
							break;
						case 2:
							level[row][col].setFillColor(sf::Color::Red);
							break;
						case 3:
							level[row][col].setFillColor(sf::Color::Green);
							break;
						case 4:
							level[row][col].setFillColor(sf::Color::Magenta);
							break;
						case 5:
							level[row][col].setFillColor(sf::Color::Cyan);
							break;
						case 6:
							level[row][col].setFillColor(sf::Color::Yellow);
							break;
						default:
							break;
						}
					}
				}
			}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // editor movement of level to the right
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					level[row][col].move(-3.7, 0);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // editor movement of level to the left
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					level[row][col].move(3.7, 0);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // editor movement of level to the left
		{
			switch (0) {
			case 0: // Play button
				m_currentGamestate = GameState::Menu;
				break;
			default:
				break;
			}
		}


	}  

	void renderEditor()
	{
		window.clear();
		
		for (int blockType = 0; blockType < 6; blockType++)
		{
			window.draw(tilePallet[blockType]);
		}

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				level[row][col].setOutlineColor(sf::Color::White);
				window.draw(level[row][col]);
			}
		}

		window.display();
	}
};

int main()
{
	Game game;

	game.init();

	game.run();

	return 0;
}