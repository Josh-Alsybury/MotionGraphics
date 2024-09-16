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

	void Walls();
	void Player();
	void Enemy();
	void Move();
	

	float Speed = -1;

	int Velocity = 2;

	float playerX = 50;

	float enemyX = 600;

	bool direction = false;

	sf::Vector2f playerPostion;

	sf::RenderWindow m_window; // main SFML window
	sf::RectangleShape m_wall;
	sf::RectangleShape m_wall2;

	sf::RectangleShape m_stripe;
	sf::RectangleShape m_stripe2;

	sf::RectangleShape m_Enemy;

	sf::RectangleShape m_player;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

