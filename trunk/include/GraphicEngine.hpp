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

/*!
*   \file GraphicEngine.hpp
*   \brief The graphic engine header
*   \version 0.1
*   \author Bastien (Bigz) Cramillet
*/

#include "../Constants.hpp"
#include "Singleton.hpp"

class Screen;

/*!
*   \class GraphicEngine
*   \brief The graphic engine which manage all the drawable objects
*/

class GraphicEngine : public Singleton<GraphicEngine>
{
    friend class Singleton<GraphicEngine>;

    public :

        /*!
        *   \brief Clear the engine by deleting all the objects it owns
        */
        void clear();

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

        /*!
        *   \brief Create a drawable circle.
        *
        *   \param xPosition The x position of the circle
        *   \param yPosition The y position of the circle
        *   \param radius The radius of the circle
        *
        *   \return A pointer on a sf::Drawable object
        */
        sf::Drawable* addCircleDrawable(float xPosition, float yPosition, float radius);

        /*!
        *   \brief Create a drawable edge.
        *
        *   \param xFirstPosition The x position of the first point composing the edge
        *   \param yFirstPosition The y position of the first point composing the edge
        *   \param xSecondPosition The x position of the second point composing the edge
        *   \param ySecondPosition The y position of the second point composing the edge
        *
        *   \return A pointer on a sf::Drawable object
        */
        sf::Drawable* addStaticEdge(float xFirstPosition, float yFirstPosition, float xSecondPosition, float ySecondPosition);

        /*!
        *   \brief Create a drawable polyline. (The function actually create a polygon and only draw
        *                                        the interesting edges)
        *
        *   \param vpCoord A vector of X and Y coordinates
        *
        *   \return A pointer on a sf::Drawable object
        */
        sf::Drawable* addStaticPolyline(std::vector<std::pair<float,float> > vpCoord);

        /*!
        *   \brief Draw all the drawable objects
        *
        *   \param screen The RenderWindow used to draw the objects
        */
        void draw (Screen& screen);


    protected :

        GraphicEngine ();                       //!< Constructor

        ~GraphicEngine ();                      //!< Destructor

        std::vector<sf::Drawable*> m_vDrawable; //!< A vector of pointer to drawable objects
};

#endif // GRAPHICENGINE_HPP_INCLUDED
