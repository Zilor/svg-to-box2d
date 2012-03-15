/*------------------------------------------------------------------------------
*
* S2B - SVG to Box2D
*
* Copyright (c) 2010-2011 Bastien Cramillet (Bigz)(bastien.cramillet@gmail.com)
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
*    1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
*
*    2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
*
*    3. This notice may not be removed or altered from any source
*   distribution.
*
*-----------------------------------------------------------------------------*/

#include "../include/Screen.hpp"
#include "../include/Object.hpp"

Screen::Screen() : sf::RenderWindow(sf::VideoMode(1024,768), "Box2D", sf::Style::Close, sf::ContextSettings(0, 0, 4, 2, 0) )
{
    setFramerateLimit(60);
}

int Screen::run (Scene& scene)
{
    sf::Vector2f Center(512,384);
    sf::Vector2f HalfSize(1024, 768);

    sf::View* view = new sf::View(Center, HalfSize);

    int circleSize = 25;
    int rectSize = 50;

    sf::CircleShape circle;
    circle.setRadius(circleSize);
    circle.setFillColor(sf::Color(255,0,0,130));
    circle.setOrigin(circleSize, circleSize);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(rectSize, rectSize));
    rect.setFillColor(sf::Color(0,0,255,130));
    rect.setOrigin(rectSize / 2.f, rectSize / 2.f);

    rect.setOrigin(rectSize / 2.f, rectSize / 2.f);

    int shape = 0;

    std::string info = "C to create a circle  \nB to Create a box \nMouse wheel to increase or decrease the object size (creation mode) \
                        \nEsc to leave the creation mode \n\nMousewheel to zomm-in or zoom-out (free mode) \nArrows to move the camera";

    sf::Text text(info);
    text.setPosition(25.f, 25.f);
    text.setScale(0.5, 0.5);

    sf::Event event;

    sf::VertexArray lines(sf::LinesStrip, 4);
 lines[0].position = sf::Vector2f(10, 0);
 lines[1].position = sf::Vector2f(20, 0);
 lines[2].position = sf::Vector2f(30, 5);
 lines[3].position = sf::Vector2f(40, 2);

    sf::Clock time;
    while (isOpen())
    {
        // Clear the render window
        clear();

        setView(*view);

        sf::Vector2f mPosition = convertCoords(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y, *view);

        // Get the keyboard and mouse events
        while (pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shape == 1)
            {
                scene.addCircle(mPosition.x, mPosition.y, circleSize);
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shape == 2)
            {
                scene.addRect(mPosition.x, mPosition.y, rectSize, rectSize);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)     view->move(0, -50);
                if (event.key.code == sf::Keyboard::Down)   view->move(0, 50);
                if (event.key.code == sf::Keyboard::Left)   view->move(-50, 0);
                if (event.key.code == sf::Keyboard::Right)  view->move(50, 0);
                if (event.key.code == sf::Keyboard::C)
                {
                    shape = 1;
                }
                if (event.key.code == sf::Keyboard::B)
                {
                    shape = 2;
                }
                if (event.key.code == sf::Keyboard::Escape)
                {
                    shape = 0;
                }
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                if (!shape)
                {
                    if (event.mouseWheel.delta == -1)   view->zoom(1.1);
                    else if (event.mouseWheel.delta == 1)    view->zoom(0.9);
                }
                else
                {
                    if (event.mouseWheel.delta == -1)
                    {
                        if (shape == 1)
                        {
                            circleSize *= 1.1;
                            circle.setRadius(circleSize);// = sf::Shape::Circle(0, 0, circleSize, sf::Color(255,0,0,130));

                        }
                        if (shape == 2)
                        {
                            rectSize *= 1.1;
                            rect.setSize(sf::Vector2f(rectSize, rectSize));// = sf::Shape::Rectangle(0,0, rectSize, rectSize, sf::Color(0,0,255,130));
                            rect.setOrigin(rectSize / 2.f, rectSize / 2.f);
                        }
                    }
                    else if (event.mouseWheel.delta == 1)
                    {
                        if (shape == 1)
                        {
                            circleSize *= 0.9;
                            circle.setRadius(circleSize);// = sf::Shape::Circle(0, 0, circleSize, sf::Color(255,0,0,130));

                        }
                        if (shape == 2)
                        {
                            rectSize *= 0.9;
                            rect.setSize(sf::Vector2f(rectSize, rectSize));//  =sf::Shape::Rectangle(0,0, rectSize, rectSize, sf::Color(0,0,255,130));
                            rect.setOrigin(rectSize / 2.f, rectSize / 2.f);
                        }
                    }
                }
            }
        }


        // Update the simulation
        PhyEngine::getInstance()->update(time.getElapsedTime().asSeconds());

        scene.update();

        // Draw the scene
        //std::cout << "predraw" << std::endl;
        GraphicEngine::getInstance()->draw(*this);
        //std::cout << "postdraw" << std::endl;

        if (shape == 1)
        {
            circle.setPosition(mPosition.x, mPosition.y);
            draw(circle);
        }
        else if (shape == 2)
        {
            rect.setPosition(mPosition.x, mPosition.y);
            draw(rect);
        }

        draw(text);

draw(lines);
        // Reset the timer
        time.restart();

        display();
    }

    return EXIT_SUCCESS;
}
