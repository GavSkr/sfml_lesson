#pragma once
#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
//#include <iostream>
#include <list>

class Snake
{
public:
	Snake() = delete;
	Snake(const int x, const int y);
	Snake(const Snake& snake) = delete;
	~Snake() {};
	//Will made = Constructer
	sf::Vector2f getSize_head();
	sf::Vector2f getPosition_head();
	void setPosition(const sf::Vector2f x_y);
	void setPosition(const float x, const float y);
	void move_auto(const int x, const int y);
	void move_auto();
	void move_manual(const int x, const int y);
	std::list<sf::RectangleShape> get_body();
	sf::RectangleShape get_head();
	void set_time(const float time, const float t);
	bool check_move(const int x, const int y);
	bool check_move();
	bool check_move_m(const int x, const int y);
	void grow(const int x, const int y);
	void grow();
	int size();
private:
	sf::RectangleShape head;
	std::list<sf::RectangleShape> body{};
	int live{ 0 };
	int step[3] { 0, -10, 10 };
	int x { 0 }, y{ 0 };
	float time{0.f};

};

#endif // SNAKE_H

