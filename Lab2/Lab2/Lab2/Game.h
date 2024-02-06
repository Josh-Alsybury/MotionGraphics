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
	void Player();
	void moveLeft();
	void moveRight();

	void setup();
	
	static const int numWalls = 90;
	sf::RectangleShape walls [numWalls];

	int wallsX = 0;
	int wallsY = 0;

};

#endif // !GAME_HPP

