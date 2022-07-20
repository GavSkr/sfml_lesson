#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <functional>
#include <thread>
#include "snake.h"


//sf::Mutex mutex;
void snake_move(sf::RectangleShape &snake_head, std::list<sf::RectangleShape>& snake, sf::RectangleShape& background_s, int x, int y, sf::Time &time);


int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!",sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(120);
    sf::Vector2u win_size = window.getSize();

    // Snake
    sf::Vector2f snake_head_size{ 10, 10 };
    sf::RectangleShape snake_head(snake_head_size);
    snake_head.setPosition(450, 450);
    snake_head.setFillColor(sf::Color::Green);
    sf::Vector2f snake_head_coor;
    

    std::list<sf::RectangleShape> snake;
    sf::Vector2f snake_coor;
    sf::RectangleShape snake_neck;
    sf::Vector2f snake_neck_coor;

    //backgound for a snake
    sf::Vector2f background_s_size{ 600, 600 };
    sf::RectangleShape background_s(background_s_size);
    background_s.setPosition(100, 150);
    background_s.setFillColor(sf::Color::Black);
    sf::Vector2f  background_s_coor = background_s.getPosition();

    //food
    sf::Texture food;
    
    if (!food.loadFromFile("D:\\demo\\Lesson_c\\sfml_lesson\\food.png"))
    {
        std::cout << "FUCK!!!!!!!! THIS TEXTURE FOOD.PNG" << std::endl;
    }

    sf::Sprite food_s;
    food_s.setTextureRect(sf::IntRect(36, 36, 48, 48));
    food_s.setTexture(food);
    //food_s.setColor(sf::Color::Cyan);
    food_s.setPosition(250,250);
    food_s.setScale(0.2f,0.2f);
    sf::Vector2f  food_s_coor;
    
    
        
    sf::Time time = sf::seconds(0.125f);
    std::srand(std::time(0));
    
    int x, y, k = 0, x1, y1; // temp variory
    int step[] = {0, -10, 10};
    bool rigth = false, left = false, up = false, down = false, m = true;

    //Theard
    sf::Thread snake_thread(std::bind(snake_move, snake_head, snake, background_s, x, y, time));

    while (window.isOpen())
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (x == 0 && y == 0);

        if (x == 0 && y == 0) // check: don't move
        {
            std::cout << "\tSTOP MOVE" << std::endl;
            //continue;
        }

        do
        {
            x1 = rand() % 3;
            y1 = rand() % 3;
        } while (x1 == 0 && y1 == 0);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        //snake_move(snake_head, snake, background_s, x, y, time);
        std::cout << "In main(): x = " << x << " and " << "y = " << y << std::endl;
        snake_thread.launch();
        

        if (snake.size() == 10)
            snake.pop_front();

        food_s_coor = food_s.getPosition();
        if (x1)
        {
            y1 = 0;
            if (food_s_coor.x + step[x1] >= background_s_coor.x && food_s_coor.x + step[x1] <= background_s_coor.x + background_s_size.x - 10)
            {
                //std::cout << "MOVE to X" << std::endl;
                food_s.move(step[x1], step[y1]);
            }
            else continue;
        }
        if (y1)
        {
            x1 = 0;
            if (food_s_coor.y + step[y1] >= background_s_coor.y && food_s_coor.y + step[y1] <= background_s_coor.y + background_s_size.y - 10)
            {
                //std::cout << "MOVE to X" << std::endl;
                food_s.move(step[x1], step[y1]);
            }
            else continue;
        }

                   
        window.clear(sf::Color::White);

        window.draw(background_s);
        window.draw(food_s);
        for (auto i : snake)
            window.draw(i);
        window.draw(snake_head);
        

        window.display();


        //std::cout << "MOVE" << std::endl;
        sf::sleep(time);
               
    }

    return 0;
}