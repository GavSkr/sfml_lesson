#pragma once
#ifdef SNAKE_H
#define SNAKE_H


void snake_move(sf::RectangleShape &snake_head, std::list<sf::RectangleShape> &snake, sf::RectangleShape &background_s, int x, int y, sf::Time& time);


#endif // SNAKE_H

