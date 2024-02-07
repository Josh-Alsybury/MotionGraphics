/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game


	sf::RectangleShape m_player;
	int Velocity = 20;
	float playerX = 400;
	float playerY = 500;
	void Player();
	void moveLeft();
	void moveRight();

	void bullet();
	void fire();
	sf::RectangleShape m_bullet;
	bool firing = false;
	float bulletY = playerY;
	float bulletX = playerX;
	float distance = 500;

	void setupFontAndText();
	void collision();
    void setup();

	bool move = false;
	bool endGame = false;
	
	static const int numWalls = 480;
	sf::RectangleShape walls [numWalls];

	int wallsX = 0;
	int wallsY = -2300;

	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Text m_endText;
};

#endif // !GAME_HPP

