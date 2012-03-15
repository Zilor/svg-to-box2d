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
    clear();
}

void GraphicEngine::clear()
{
    std::for_each(m_vDrawable.begin(), m_vDrawable.end(), Delete());
}

sf::Drawable* GraphicEngine::addBoxDrawable(float xPosition, float yPosition, float xSize, float ySize)
{
    // Creation of a shape
    sf::RectangleShape* rect = new sf::RectangleShape();

    rect->setSize(sf::Vector2f(xSize, ySize));
    rect->setOrigin(xSize / 2.f, ySize / 2.f);
    rect->setPosition(xPosition, yPosition);
    rect->setFillColor(sf::Color(0,0,255,255));

    // Add the shape to the list of drawable of the engine
    m_vDrawable.push_back(rect);

    return rect;
}

sf::Drawable* GraphicEngine::addStaticBoxDrawable(float xPosition, float yPosition, float xSize, float ySize)
{
    sf::RectangleShape* rect = new sf::RectangleShape();

    rect->setSize(sf::Vector2f(xSize, ySize));
    rect->setOrigin(xSize / 2.f, ySize / 2.f);
    rect->setPosition(xPosition, yPosition);
    rect->setFillColor(sf::Color(255,255,255,255));

    m_vDrawable.push_back(rect);

    return rect;
}

sf::Drawable* GraphicEngine::addCircleDrawable(float xPosition, float yPosition, float radius)
{
    sf::CircleShape* circle = new sf::CircleShape();
    circle->setRadius(radius);
    circle->setOrigin(radius, radius);
    circle->setPosition(xPosition, yPosition);
    circle->setFillColor(sf::Color(255,0,0,255));

    m_vDrawable.push_back(circle);

    return circle;
}

sf::Drawable* GraphicEngine::addStaticEdge(float xFirstPosition, float yFirstPosition, float xSecondPosition, float ySecondPosition)
{
    sf::RectangleShape* edge = new sf::RectangleShape();

    m_vDrawable.push_back(edge);

    return edge;
}

sf::Drawable* GraphicEngine::addStaticPolyline(std::vector<std::pair<float,float> > vpCoord)
{
    int size = vpCoord.size();
    sf::VertexArray* polyline = new sf::VertexArray(sf::LinesStrip, size);
    for (int i = 0; i < size; ++i)
    {
        sf::Vertex vertex;
        vertex.position = sf::Vector2f(vpCoord[i].first, vpCoord[i].second);
        polyline->append(vertex);
    }
    m_vDrawable.push_back(polyline);

    return polyline;
}

void GraphicEngine::draw (Screen& screen)
{
    // Draw each shape on the screen
    int size = m_vDrawable.size();
    for (int i = 0; i < size; ++i)
    {
        screen.draw(*m_vDrawable[i]);
    }
}
