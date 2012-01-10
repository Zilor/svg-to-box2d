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

#ifndef GRAPHICENGINE_HPP_INCLUDED
#define GRAPHICENGINE_HPP_INCLUDED

#include "../Constants.hpp"
#include "Singleton.hpp"

class Screen;

class GraphicEngine : public Singleton<GraphicEngine>
{
    friend class Singleton<GraphicEngine>;

    public :

        /*!
        *   \brief Create a drawable rectangle.
        *
        *   \param xPosition The x position of the rectangle
        *   \param yPosition The y position of the rectangle
        *   \param xSize The width of the rectangle
        *   \param ySize The height of the rectangle
        *
        *   \return A pointer on a sf::Drawable object
        */
        sf::Drawable* addBoxDrawable(float xPosition, float yPosition, float xSize, float ySize);

        /*!
        *   \brief Create a drawable rectangle. For a static box, the color change compare to a
        *           dynamic box.
        *
        *   \param xPosition The x position of the rectangle
        *   \param yPosition The y position of the rectangle
        *   \param xSize The width of the rectangle
        *   \param ySize The height of the rectangle
        *
        *   \return A pointer on a sf::Drawable object
        */
        sf::Drawable* addStaticBoxDrawable(float xPosition, float yPosition, float xSize, float ySize);

        sf::Drawable* addCircleDrawable(float xPosition, float yPosition, float radius);

        sf::Drawable* addStaticEdge(float xFirstPosition, float yFirstPosition, float xSecondPosition, float ySecondPosition);

        sf::Drawable* addStaticPolyline(std::vector<std::pair<float,float> > vpCoord);

        void draw (Screen& screen);


    protected :

        GraphicEngine ();

        ~GraphicEngine ();

        std::vector<sf::Drawable*> m_vDrawable;
};

#endif // GRAPHICENGINE_HPP_INCLUDED
