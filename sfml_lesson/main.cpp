#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void sh_m(sf::CircleShape* shape)
{
    sf::Vector2f p_sh;
    while (true)
    {
        //sf::sleep(sf::milliseconds(100));
        shape->move(0.1, 0);
        std::cout << "shape.move\n";
        p_sh = shape->getPosition();
        if (p_sh.x > 850)
            shape->setPosition(50, 150);
     }
}


void sh_m1(sf::CircleShape* shape)
{
    while (true)
    {
        sf::sleep(sf::milliseconds(100));
        shape->move(0.11, 0);
        std::cout << "\t\tSHAPE1.MOVE\n";
      
    }
}

void n_w()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "Seconds window!");
    window.setFramerateLimit(1);
    int i = 0;
    while (window.isOpen())
    {
        sf::Event event;
        //sf::Thread t_e([&]()
        //    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        
        std::vector<sf::Color> vc = {sf::Color::Black, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta, sf::Color::Red, sf::Color::White, sf::Color::Yellow};
        
        if (i == vc.size())
            i = 0;

        window.clear(vc[i]);

        ++i;

        window.display();
        
    }
    
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
    window.setFramerateLimit(120);
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(50, 50);
    shape.setPosition(50, 150);

    sf::CircleShape shape1(50.f);
    shape1.setFillColor(sf::Color::Red);
    shape1.setOrigin(50, 50);
    shape1.setPosition(50, 350);

    sf::Thread t_sh(&sh_m,&shape);
    sf::Thread t_sh1(&sh_m1, &shape1);
    sf::Thread t_nw1(&n_w);

    int i = 0, k = 0, h = 0;

    t_sh.launch();

    t_sh1.launch();

    t_nw1.launch();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
             {
                 if (event.type == sf::Event::Closed)
                     window.close();

             }
            
        i += 10;
        k += 5;
        h = i + k;
        if (i > 255)
            i == 0;
        if (k > 255)
            k == 0;
        if (h > 255)
            h == 0;
       
               
        window.clear(sf::Color(i,k,h));

        window.draw(shape);
        window.draw(shape1);

        window.display();
        
    }

    return 0;
}