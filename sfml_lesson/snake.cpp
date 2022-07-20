#include "snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

//sf::Mutex mutex;
int k = 0; // temp variables
int step[] = { 0, -10, 10 };
bool m = true;

sf::Vector2f snake_head_size;
sf::Vector2f snake_coor;
sf::RectangleShape snake_neck;
sf::Vector2f snake_neck_coor;
sf::Vector2f snake_head_coor;
sf::Vector2f background_s_coor;
sf::Vector2f background_s_size;

void snake_move(sf::RectangleShape &snake_head, std::list<sf::RectangleShape> &snake, sf::RectangleShape &background_s, int x, int y, sf::Time& time)
{
    //mutex.lock();
    sf::sleep(time);
    
    snake_head_size = snake_head.getSize();
    snake_head_coor = snake_head.getPosition();
    sf::Vector2f  background_s_coor = background_s.getPosition();
    sf::Vector2f background_s_size = background_s.getSize();
    m = true;
    if (snake.size())
    {
        snake_neck_coor = snake_neck.getPosition();

        if (x)
        {
            y = 0;
            if (snake_head_coor.x + step[x] >= background_s_coor.x && snake_head_coor.x + step[x] <= background_s_coor.x + background_s_size.x - snake_head_size.x)
            {
                //std::cout << "MOVE to X" << std::endl;
                k = 0;
                for (auto i = snake.rbegin(); k <= 4 && i != snake.rend(); i++, ++k)
                {
                    snake_neck_coor = i->getPosition();
                    if (snake_neck_coor.x == snake_head_coor.x + step[x] && snake_neck_coor.y == snake_head_coor.y + step[y])
                    {
                        m = false;
                    }
                }

                if (m)//(snake_neck_coor.x != snake_head_coor.x + step[x])
                {

                    std::cout << "MOVE to X" << std::endl;
                    snake_neck = snake_head;
                    snake_neck.setFillColor(sf::Color::Red);
                    snake.push_back(sf::RectangleShape(snake_neck));
                    snake_head.move(step[x], step[y]);
                }
                else return;
            }
            else return;
        }
        if (y)
        {
            x = 0;
            if (snake_head_coor.y + step[y] >= background_s_coor.y && snake_head_coor.y + step[y] <= background_s_coor.y + background_s_size.y - snake_head_size.x)
            {
                //std::cout << "MOVE to Y" << std::endl;
                k = 0;
                for (auto i = snake.rbegin(); k <= 4 && i != snake.rend(); i++, ++k)
                {
                    snake_neck_coor = i->getPosition();
                    if (snake_neck_coor.x == snake_head_coor.x + step[x] && snake_neck_coor.y == snake_head_coor.y + step[y])
                    {
                        m = false;
                    }
                }

                if (m)//(snake_neck_coor.y != snake_head_coor.y + step[y])
                {
                    std::cout << "\tMOVE to Y" << std::endl;
                    snake_neck = snake_head;
                    snake_neck.setFillColor(sf::Color::Red);
                    snake.push_back(sf::RectangleShape(snake_neck));
                    snake_head.move(step[x], step[y]);
                }
                else return;
            }
            else return;
        }
    }
    else
    {
        if (x)//gorizont move
        {
            y = 0;
            snake_neck = snake_head;
            snake_neck.setFillColor(sf::Color::Red);
            snake.push_back(sf::RectangleShape(snake_neck));
            snake_head.move(step[x], step[y]);
        }
        if (y)//vertical move
        {
            x = 0;
            snake_neck = snake_head;
            snake_neck.setFillColor(sf::Color::Red);
            snake.push_back(sf::RectangleShape(snake_neck));
            snake_head.move(step[x], step[y]);
        }
    }


}
