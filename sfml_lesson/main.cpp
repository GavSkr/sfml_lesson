#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include<functional>
#include "Snake.h"
#include "map.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "Generation of password by SFML!",sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(10);
    sf::Vector2u win_size = window.getSize();
    //icon window
    sf::Image icon_image;
    icon_image.loadFromFile("images\\icon.png");
    icon_image.createMaskFromColor(sf::Color::White);
    window.setIcon(icon_image.getSize().x, icon_image.getSize().y, icon_image.getPixelsPtr());

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

    sf::Text codeText("Code: ", font, 20);
    codeText.setFillColor(sf::Color::Black);
    codeText.setPosition(50, 800);
    std::string code{};

    sf::Text symText("Symbols Dec: eat \"food\"", font, 20);
    symText.setFillColor(sf::Color::Black);
    symText.setPosition(50, 750);
    std::string sym{};

    sf::Text snakeText("Snake length: ", font, 20);
    snakeText.setFillColor(sf::Color::Black);
    snakeText.setPosition(550, 50);
    std::string snakeLengh{};

    sf::Text copy1_Text("COPY", font, 10);
    copy1_Text.setFillColor(sf::Color::Black);
    copy1_Text.setPosition(550, 760);
    sf::Text copy2_Text("COPY", font, 10);
    copy2_Text.setFillColor(sf::Color::Black);
    copy2_Text.setPosition(550, 810);
   

    // Snake
    Snake s(200, 400);

    //backgound for a snake
    sf::Vector2f background_s_size{ 550, 550 };
    sf::RectangleShape background_s(background_s_size);
    background_s.setPosition(100, 150);
    background_s.setFillColor(sf::Color::Black);

    //button
    sf::Vector2f button_s_size{ 60, 30 };
    sf::RectangleShape button1_s(button_s_size);
    button1_s.setPosition(530, 750);
    button1_s.setOutlineColor(sf::Color::Black);
    button1_s.setOutlineThickness(1.f);

    sf::RectangleShape button2_s(button_s_size);
    button2_s.setPosition(530, 800);
    button2_s.setOutlineColor(sf::Color::Black);
    button2_s.setOutlineThickness(1.f);

    //map
    sf::Image map_i;
    map_i.loadFromFile("images\\map.png");
    sf::Texture map_t;
    map_t.loadFromImage(map_i);
    sf::Sprite map_s;
    map_s.setTexture(map_t);

    //food
    sf::Image food_image;
    food_image.loadFromFile("images\\food.png");
    food_image.createMaskFromColor(sf::Color::Black);
    sf::Texture food_texture;
    food_texture.loadFromImage(food_image);
    if (!food_texture.loadFromImage(food_image))
    {
        std::cout << "FUCK!!!!!!!! THIS TEXTURE FOOD.PNG" << std::endl;
    }
    sf::Sprite food_s;
    food_s.setTexture(food_texture);
    food_s.setTextureRect(sf::IntRect(36, 36, 48, 48));
    //food_s.setColor(sf::Color::Cyan);
    food_s.setPosition(250,250);
    food_s.setScale(0.2f,0.2f);
    //sf::Vector2f  food_s_coor;

    //temp variables
    int x, y, x1, y1; 
    float fps = 0.f;
    float step[] = {0.f, -10.f, 10.f};
    bool rigth = true, left = true, up = true, down = true, m = true;

     
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
            x1 = rand() % 3;
            y1 = rand() % 3;
        } while (x1 == 0 && y1 == 0);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
       
      
        if (window.hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rigth)
        {
            left = false;
            rigth = false;
            up = true;
            down = true;
            s.move_manual(10, 0);
        }
        if (window.hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && left)
        {
            left = false;
            rigth = false;
            up = true;
            down = true;
            s.move_manual(-10, 0);
        }
        if (window.hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && down)
        {
            left = true;
            rigth = true;
            up = false;
            down = false;
            s.move_manual(0, 10);
        }
        if (window.hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && up)
        {
            left = true;
            rigth = true;
            up = false;
            down = false;
            s.move_manual(0, -10);
        }
        
        s.move_auto();
        if (food_s.getPosition() == s.getPosition_head())
        {
            s.grow();

            codeText.setString("");
            code.erase();
            symText.setString("");
            sym.erase();
            for (int i = 0; i < 10; ++i)
            {
                char c;
                int g = rand() % 127;
                if (g < 33) g += 33;
                c = g;
                code.push_back(c);
                sym += std::to_string(g);
            }
            codeText.setString("Code: " + code);
            symText.setString("Sym Dec: " + sym);
        }
          
        //check zone
        if (s.getPosition_head().x < background_s.getPosition().x)
        {
            s.setPosition(background_s.getPosition().x + background_s_size.x - s.getSize_head().x, s.getPosition_head().y);
        }
        if (s.getPosition_head().x >= background_s.getPosition().x + background_s_size.x)
        {
            s.setPosition(background_s.getPosition().x, s.getPosition_head().y);
        }
        if (s.getPosition_head().y < background_s.getPosition().y)
        {
            s.setPosition(s.getPosition_head().x, background_s.getPosition().y + background_s_size.y - s.getSize_head().y);
        }
        if (s.getPosition_head().y >= background_s.getPosition().y + background_s_size.y)
        {
            s.setPosition(s.getPosition_head().x, background_s.getPosition().y);
        }

        //press button
        bool focus_button1 = (sf::Mouse::getPosition(window).x >= button1_s.getPosition().x && sf::Mouse::getPosition(window).x <= button1_s.getPosition().x + button1_s.getSize().x) &&
            (sf::Mouse::getPosition(window).y >= button1_s.getPosition().y && sf::Mouse::getPosition(window).y <= button1_s.getPosition().y + button1_s.getSize().y);
        bool focus_button2 = (sf::Mouse::getPosition(window).x >= button2_s.getPosition().x && sf::Mouse::getPosition(window).x <= button2_s.getPosition().x + button2_s.getSize().x) &&
            (sf::Mouse::getPosition(window).y >= button2_s.getPosition().y && sf::Mouse::getPosition(window).y <= button2_s.getPosition().y + button2_s.getSize().y);
        if (focus_button1)
        {
            button1_s.setFillColor(sf::Color::Yellow);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                button1_s.setFillColor(sf::Color::Red);
                sf::Clipboard::setString(sym);
            }
        }
        else
            button1_s.setFillColor(sf::Color::White);
        
        if (focus_button2)
        {
            button2_s.setFillColor(sf::Color::Yellow);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                button2_s.setFillColor(sf::Color::Red);
                sf::Clipboard::setString(code);
            }
        }
        else
            button2_s.setFillColor(sf::Color::White);

        //food_s_coor = food_s.getPosition();
        if (x1)
        {
            y1 = 0;
            if (food_s.getPosition().x + step[x1] >= background_s.getPosition().x && food_s.getPosition().x + step[x1] <= background_s.getPosition().x + background_s_size.x - 10)
            {
                //std::cout << "MOVE to X" << std::endl;
                food_s.move(step[x1], step[y1]);
            }
            else continue;
        }
        if (y1)
        {
            x1 = 0;
            if (food_s.getPosition().y + step[y1] >= background_s.getPosition().y && food_s.getPosition().y + step[y1] <= background_s.getPosition().y + background_s_size.y - 10)
            {
                //std::cout << "MOVE to X" << std::endl;
                food_s.move(step[x1], step[y1]);
            }
            else continue;
        }



        //std::cout << "TIME: " << time << std::endl;
        fps_string.str("");
        fps_string << int(time);
        timeText.setString("Time: " + fps_string.str() + "\tsec.");

        fps_string.str("");
        fps_string << frame;
        frameText.setString("Frame: " + fps_string.str());

        snakeLengh.erase();
        snakeLengh = std::to_string(s.size());
        snakeText.setString("Snake length: " + snakeLengh);

         
        window.clear(sf::Color::White);

        window.draw(button1_s);
        window.draw(button2_s);

        window.draw(fpsText);
        window.draw(timeText);
        window.draw(frameText);
        window.draw(codeText);
        window.draw(symText);
        window.draw(snakeText);
        window.draw(copy1_Text);
        window.draw(copy2_Text);

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
        
        window.draw(food_s);

        for (auto i: s.get_body())//(auto i = s.get_snake().rbegin(); i != s.get_snake().rend(); i++)
            window.draw(i);


        window.draw(s.get_head());

        window.display();

        ++frame;
        previousTime = currentTime;
    }

    return 0;
}