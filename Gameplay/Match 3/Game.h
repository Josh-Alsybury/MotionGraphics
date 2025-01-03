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

	void wallsetup();
	void blockSetup();
	void mousePoint();
	void match();

	const static int NUM_WALLS = 37;
	const static int FRUIT = 100;
	sf::RectangleShape Walls[NUM_WALLS];

	sf::RectangleShape fruits[FRUIT];
	float blockx = 10; 
	float blocky = 10;  

	sf::CircleShape mPoint;

	sf::RectangleShape colour1;
	sf::RectangleShape colour2;
	sf::RectangleShape colour3;

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

