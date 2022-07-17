#include <SFML/Graphics.hpp>
#include <iostream>
//#include <vector>
#include <list>


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

        
    sf::Time time = sf::seconds(0.125f);
    std::srand(std::time(0));
    
    int x, y, i; // temp variory
    i = 0;
    int step[] = {0, -10, 10};
    bool rigth = false, left = false, up = false, down = false, m = true;


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
            continue;
        }
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        snake_head_coor = snake_head.getPosition();
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
                    for (auto i = snake.rbegin(); i != snake.rend(); i++)
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
                    else continue;
                }
                else continue;
            }
            if (y)
            {
                x = 0;
                if (snake_head_coor.y + step[y] >= background_s_coor.y && snake_head_coor.y + step[y] <= background_s_coor.y + background_s_size.y - snake_head_size.x)
                {
                    //std::cout << "MOVE to Y" << std::endl;
                    for (auto i = snake.rbegin(); i != snake.rend(); i++)
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
                    else continue;
                }
                else continue;
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
        
        if (snake.size() == 10)
            snake.pop_front();

        window.clear(sf::Color::White);

        window.draw(background_s);
        for (auto i : snake)
            window.draw(i);
        window.draw(snake_head);

        window.display();


        /*td::vector<int> v{ 1,2,3,4,5,6,7,8,9,0 };
        
        for (auto i = v.rbegin(); i != v.rend(); i++)
            std::cout << *i << "\t";
        std::cout << std::endl;*/

        //std::cout << "MOVE" << std::endl;
        sf::sleep(time);
               
    }

    return 0;
}