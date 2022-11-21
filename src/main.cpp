#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include <fstream>
sf::RenderWindow window(sf::VideoMode(900, 900), "Drawing", sf::Style::Close);

int main()
{
    std::vector<sf::CircleShape> dots;
    bool isDrawing = false;

    window.setFramerateLimit(120);

    while (window.isOpen())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                isDrawing = true;
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                isDrawing = false;
            }
        }

        std::ifstream fileIn("mpsync");
        std::string lineContent;
        if (fileIn)
        {
            sf::CircleShape dot;
            dot.setRadius(10.f);
            dot.setFillColor(sf::Color::White);
            dot.setOrigin(sf::Vector2f(5, 5));
            float dotX, dotY = 0;
            for (size_t i = 0; std::getline(fileIn, lineContent); i++)
            {
                if (i == 0 && lineContent.size() > 0)
                {
                    dotX = std::stof(lineContent);
                }
                else if (i == 1 && lineContent.size() > 0)
                {
                    dotY = std::stof(lineContent);
                }
                else
                {
                    break;
                }
            }
            dot.setPosition(sf::Vector2f(dotX, dotY));
            dots.push_back(dot);
        }
        fileIn.close();

        if (isDrawing)
        {
            sf::CircleShape dot;
            float dotX, dotY = 0;
            dot.setRadius(10.f);
            dot.setFillColor(sf::Color::Red);
            dot.setOrigin(sf::Vector2f(5, 5));
            dotX = mousePos.x - window.getPosition().x;
            dotY = mousePos.y - window.getPosition().y;
            dot.setPosition(sf::Vector2f(dotX, dotY));
            dots.push_back(dot);

            std::ofstream fileOut("mpsync");
            if (fileOut)
            {
                fileOut << dotX << std::endl
                        << dotY;
            }
            else
                return 1;
            fileOut.close();
        }

        window.clear();
        for (size_t i = 0; i < dots.size(); i++)
        {
            window.draw(dots[i]);
        }

        window.display();
    }

    return 0;
}