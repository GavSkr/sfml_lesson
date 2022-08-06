#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include<functional>
#include "Snake.h"
#include "map.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML Snake!",sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Vector2u win_size = window.getSize();

    //text
    sf::Font font;
    font.loadFromFile("fonts\\sansation.ttf");
    if (!font.loadFromFile("fonts\\sansation.ttf"))
       std::cout << "Fuck FONT" << std::endl;
    sf::Text fpsText("FPS: ", font, 20);
    fpsText.setFillColor(sf::Color::Black);
    fpsText.setPosition(50, 50);

    sf::Text timeText("Time: ", font, 20);
    timeText.setFillColor(sf::Color::Black);
    timeText.setPosition(200, 50);

    sf::Text frameText("Frame: ", font, 20);
    frameText.setFillColor(sf::Color::Black);
    frameText.setPosition(400, 50);
    int frame = 0;
   

    // Snake
    Snake s(200, 400);

    //backgound for a snake
    sf::Vector2f background_s_size{ 550, 550 };
    sf::RectangleShape background_s(background_s_size);
    background_s.setPosition(100, 150);
    background_s.setFillColor(sf::Color::Black);

    //map
    sf::Image map_i;
    map_i.loadFromFile("images\\map.png");
    sf::Texture map_t;
    map_t.loadFromImage(map_i);
    sf::Sprite map_s;
    map_s.setTexture(map_t);

    //food
    //sf::Image food_image;
    //food_image.loadFromFile("images\\food.png");
    //sf::Texture food_texture;
    //food_texture.loadFromImage(food_image);
    //if (!food_texture.loadFromImage(food_image))
    //{
    //    std::cout << "FUCK!!!!!!!! THIS TEXTURE FOOD.PNG" << std::endl;
    //}
    //sf::Sprite food_s;
    //food_s.setTexture(food_texture);
    //food_s.setTextureRect(sf::IntRect(36, 36, 48, 48));
    ////food_s.setColor(sf::Color::Cyan);
    //food_s.setPosition(250,250);
    //food_s.setScale(0.2f,0.2f);
    //sf::Vector2f  food_s_coor;

    //temp variables
    int x, y; 
    float fps = 0.f;
    float step[] = {0.f, -10.f, 10.f};
    bool rigth = false, left = false, up = false, down = false, m = true;

     
    //Time
    std::srand(std::time(0));
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    float time = 0.f;
    
    while (window.isOpen())
    {
        std::ostringstream fps_string;
        //time = clock.getElapsedTime().asMilliseconds();
        time = clock.getElapsedTime().asSeconds();
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        fps_string << int(fps);
        fpsText.setString("FPS: " + fps_string.str());
 
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

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
       
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            s.setPosition_snake(400, 400);
        };
        
          
        float t = 0.5f;
        s.set_time(time, t);
        if (x)
        {
            y = 0;
            if (s.getPosition_head().x + step[x] >= background_s.getPosition().x && s.getPosition_head().x + step[x] <= background_s.getPosition().x + background_s_size.x - s.getSize_head().x)
            {
                if(s.check_move(x, y))
                    s.move(x, y);
                else continue;
            }
            else continue;
        }
        if (y)
        {
            x = 0;
            if (s.getPosition_head().y + step[y] >= background_s.getPosition().y && s.getPosition_head().y + step[y] <= background_s.getPosition().y + background_s_size.y - s.getSize_head().y)
            {
                if (s.check_move(x, y))
                    s.move(x, y);
                else continue;
            }
            else continue;
        }


        //food_s_coor = food_s.getPosition();
        //if (x1)
        //{
        //    y1 = 0;
        //    if (food_s_coor.x + step[x1] >= background_s_coor.x && food_s_coor.x + step[x1] <= background_s_coor.x + background_s_size.x - 10)
        //    {
        //        //std::cout << "MOVE to X" << std::endl;
        //        //food_s.move(step[x1] * time, step[y1] * time);
        //    }
        //    else continue;
        //}
        //if (y1)
        //{
        //    x1 = 0;
        //    if (food_s_coor.y + step[y1] >= background_s_coor.y && food_s_coor.y + step[y1] <= background_s_coor.y + background_s_size.y - 10)
        //    {
        //        //std::cout << "MOVE to X" << std::endl;
        //        //food_s.move(step[x1] * time, step[y1] * time);
        //    }
        //    else continue;
        //}

        std::cout << "TIME: " << time << std::endl;
        fps_string.str("");
        fps_string << int(time);
        timeText.setString("Time: " + fps_string.str() + "\tsec.");

        fps_string.str("");
        fps_string << frame;
        frameText.setString("Frame: " + fps_string.str());
        
        window.clear(sf::Color::White);

        window.draw(fpsText);
        window.draw(timeText);
        window.draw(frameText);

        

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  map_s.setTextureRect(sf::IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
                if (TileMap[i][j] == 's')  map_s.setTextureRect(sf::IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
                if ((TileMap[i][j] == '0')) map_s.setTextureRect(sf::IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


                map_s.setPosition(j * 32 + 68, i * 32 + 125);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                window.draw(map_s);//рисуем квадратики на экран
            }

        //window.draw(background_s);
        
        //window.draw(food_s);

        for (auto i: s.get_body())//(auto i = s.get_snake().rbegin(); i != s.get_snake().rend(); i++)
            window.draw(i);


        window.draw(s.get_head());

        window.display();

        ++frame;
        previousTime = currentTime;
    }

    return 0;
}