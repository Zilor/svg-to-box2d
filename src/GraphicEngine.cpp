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

#include "../include/GraphicEngine.hpp"
#include "../include/Screen.hpp"

GraphicEngine::GraphicEngine()
{

}

GraphicEngine::~GraphicEngine()
{
    std::for_each(m_vDrawable.begin(), m_vDrawable.end(), Delete());

}

sf::Drawable* GraphicEngine::addBoxDrawable(float xPosition, float yPosition, float xSize, float ySize)
{
    // Creation of a shape
    sf::Shape* rect = new sf::Shape();

    // adding the 4 points which compose the shape
    rect->AddPoint(sf::Vector2f(xSize / 2.f, ySize / 2.f));
    rect->AddPoint(sf::Vector2f(-xSize / 2.f, ySize / 2.f));
    rect->AddPoint(sf::Vector2f(-xSize / 2.f, -ySize / 2.f));
    rect->AddPoint(sf::Vector2f(xSize / 2.f, -ySize / 2.f));
    rect->SetColor(sf::Color(0,0,255,255));

    // Add the shape to the list of drawable of the engine
    m_vDrawable.push_back(rect);

    return rect;
}

sf::Drawable* GraphicEngine::addStaticBoxDrawable(float xPosition, float yPosition, float xSize, float ySize)
{
    sf::Shape* rect = new sf::Shape();

    rect->AddPoint(sf::Vector2f(xSize / 2.f, ySize / 2.f));
    rect->AddPoint(sf::Vector2f(-xSize / 2.f, ySize / 2.f));
    rect->AddPoint(sf::Vector2f(-xSize / 2.f, -ySize / 2.f));
    rect->AddPoint(sf::Vector2f(xSize / 2.f, -ySize / 2.f));
    rect->SetColor(sf::Color(255,255,255,255));

    m_vDrawable.push_back(rect);

    return rect;
}

sf::Drawable* GraphicEngine::addCircleDrawable(float xPosition, float yPosition, float radius)
{
    sf::Shape* circle = new sf::Shape();
    *circle = sf::Shape::Circle(0, 0, radius, sf::Color(255,0,0,255));

    m_vDrawable.push_back(circle);

    return circle;
}

sf::Drawable* GraphicEngine::addStaticEdge(float xFirstPosition, float yFirstPosition, float xSecondPosition, float ySecondPosition)
{
    sf::Shape* edge = new sf::Shape();

    edge->AddPoint(sf::Vector2f(xFirstPosition, yFirstPosition));
    edge->AddPoint(sf::Vector2f(xSecondPosition, ySecondPosition));

    edge->SetColor(sf::Color(255,255,255,255));

    m_vDrawable.push_back(edge);

    return edge;
}

sf::Drawable* GraphicEngine::addStaticPolyline(std::vector<std::pair<float,float> > vpCoord)
{
    sf::Shape* polyline = new sf::Shape();

    int size = vpCoord.size();

    //polyline->AddPoint(vpCoord[0].first , vpCoord[0].second, sf::Color(255,255,255,0));
    polyline->AddPoint(vpCoord[0].first , vpCoord[0].second, sf::Color(255,255,255,255));

    for (int i = 0; i < size; ++i)
    {
        sf::Vector2f p1(vpCoord[i].first, vpCoord[i].second);
        sf::Vector2f p2(vpCoord[i+1].first, vpCoord[i+1].second);

        /*sf::Vector2f normal;
        //Compute normal
        normal.x = p1.y - p2.y;
        normal.y = p2.x - p1.x;
        float len = std::sqrt(normal.x * normal.x + normal.y * normal.y);
        normal.x /= len;
        normal.y /= len;

        normal *= 2.f;*/

        polyline->AddPoint(p1 , sf::Color(255,255,255,255));
        polyline->SetPointOutlineColor(i, sf::Color(255,255,255,255));
        //if (i == vpCoord.size()-1)
            //polyline->AddPoint(p2 , sf::Color(255,255,255,100));
    }

    polyline->AddPoint(vpCoord[size].first , vpCoord[size].second, sf::Color(255,255,255,255));
    //polyline->AddPoint(vpCoord[size].first , vpCoord[size].second, sf::Color(255,255,255,0));
    polyline->EnableFill(false);
    polyline->SetOutlineThickness(2.0f);
    /*for (int i = vpCoord.size() - 1; i >= 0; --i)
    {
        sf::Vector2f p1(vpCoord[i].first, vpCoord[i].second);
        sf::Vector2f p2(vpCoord[i-1].first, vpCoord[i-1].second);

        /*sf::Vector2f normal;
        //Compute normal
        normal.x = p1.y - p2.y;
        normal.y = p2.x - p1.x;
        float len = std::sqrt(normal.x * normal.x + normal.y * normal.y);
        normal.x /= len;
        normal.y /= len;

        normal *= 2.f;

        polyline->AddPoint(p1 , sf::Color(0,255,255,100));
        //if (i == 2)
            //polyline->AddPoint(p2 , sf::Color(255,255,255,100));
            std::cout << p1.x << "   " << p1.y << std::endl;
    }*/

    m_vDrawable.push_back(polyline);

    return polyline;
}

void GraphicEngine::draw (Screen& screen)
{
    // Draw each shape on the screen
    int size = m_vDrawable.size();
    for (int i = 0; i < size; ++i)
    {
        screen.Draw(*m_vDrawable[i]);
    }
}
