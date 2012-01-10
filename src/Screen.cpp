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
    SetFramerateLimit(60);
}

int Screen::run (Scene& scene)
{
    sf::Vector2f Center(512,384);
    sf::Vector2f HalfSize(1024, 768);

    sf::View* view = new sf::View(Center, HalfSize);

    int circleSize = 25;
    int rectSize = 50;

    sf::Shape circle = sf::Shape::Circle(0, 0, circleSize, sf::Color(255,0,0,130));

    sf::Shape rect = sf::Shape::Rectangle(0,0, rectSize, rectSize, sf::Color(0,0,255,130));
    rect.SetOrigin(rectSize / 2.f, rectSize / 2.f);

    int shape = 0;

    sf::Event event;

    sf::Clock time;
    while (IsOpened())
    {
        // Clear the render window
        Clear();

        SetView(*view);

        sf::Vector2f mPosition = ConvertCoords(sf::Mouse::GetPosition(*this).x, sf::Mouse::GetPosition(*this).y, *view);

        // Get the keyboard and mouse events
        while (PollEvent(event))
        {
            if (event.Type == sf::Event::Closed)
            {
                Close();
            }
            if (sf::Mouse::IsButtonPressed(sf::Mouse::Left) && shape == 1)
            {
                scene.addCircle(mPosition.x, mPosition.y, circleSize);
            }
            else if (sf::Mouse::IsButtonPressed(sf::Mouse::Left) && shape == 2)
            {
                scene.addRect(mPosition.x, mPosition.y, rectSize, rectSize);
            }
            if (event.Type == sf::Event::KeyPressed)
            {
                if (event.Key.Code == sf::Keyboard::Up)     view->Move(0, -50);
                if (event.Key.Code == sf::Keyboard::Down)   view->Move(0, 50);
                if (event.Key.Code == sf::Keyboard::Left)   view->Move(-50, 0);
                if (event.Key.Code == sf::Keyboard::Right)  view->Move(50, 0);
                if (event.Key.Code == sf::Keyboard::C)
                {
                    shape = 1;
                }
                if (event.Key.Code == sf::Keyboard::B)
                {
                    shape = 2;
                }
                if (event.Key.Code == sf::Keyboard::Escape)
                {
                    shape = 0;
                }
            }
            if (event.Type == sf::Event::MouseWheelMoved)
            {
                if (!shape)
                {
                    if (event.MouseWheel.Delta == -1)   view->Zoom(1.1);
                    else if (event.MouseWheel.Delta == 1)    view->Zoom(0.9);
                }
                else
                {
                    if (event.MouseWheel.Delta == -1)
                    {
                        if (shape == 1)
                        {
                            circleSize *= 1.1;
                            circle = sf::Shape::Circle(0, 0, circleSize, sf::Color(255,0,0,130));

                        }
                        if (shape == 2)
                        {
                            rectSize *= 1.1;
                            rect = sf::Shape::Rectangle(0,0, rectSize, rectSize, sf::Color(0,0,255,130));
                            rect.SetOrigin(rectSize / 2.f, rectSize / 2.f);
                        }
                    }
                    else if (event.MouseWheel.Delta == 1)
                    {
                        if (shape == 1)
                        {
                            circleSize *= 0.9;
                            circle = sf::Shape::Circle(0, 0, circleSize, sf::Color(255,0,0,130));

                        }
                        if (shape == 2)
                        {
                            rectSize *= 0.9;
                            rect = sf::Shape::Rectangle(0,0, rectSize, rectSize, sf::Color(0,0,255,130));
                            rect.SetOrigin(rectSize / 2.f, rectSize / 2.f);
                        }
                    }
                }
            }
        }


        // Update the simulation
        PhyEngine::getInstance()->update(time.GetElapsedTime() / 1000.f);

        scene.update();

        // Draw the scene
        GraphicEngine::getInstance()->draw(*this);

        if (shape == 1)
        {
            circle.SetPosition(mPosition.x, mPosition.y);
            Draw(circle);
        }
        else if (shape == 2)
        {
            rect.SetPosition(mPosition.x, mPosition.y);
            Draw(rect);
        }

        std::cout << time.GetElapsedTime() << std::endl;


        // Reset the timer
        time.Reset();

        Display();
    }

    return EXIT_SUCCESS;
}
