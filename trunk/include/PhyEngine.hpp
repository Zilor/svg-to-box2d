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

#ifndef PHYENGINE_HPP_INCLUDED
#define PHYENGINE_HPP_INCLUDED

/*!
*   \file PhyEngine.hpp
*   \brief The physic engine header
*   \version 0.1
*   \author Bastien (Bigz) Cramillet
*/

#include "../Constants.hpp"
#include "Singleton.hpp"

/*!
*   \class PhyEngine
*   \brief The physic engine which simulate the physical world
*           and manage all the physical objects
*/

class PhyEngine : public Singleton<PhyEngine>
{
    friend class Singleton<PhyEngine>;

    public :

        /*!
        *   \brief Initialize the PhyEngine
        */
        void init ();

        /*!
        *   \brief Clear the world
        */
        void clear ();

        /*!
        *   \brief Update the world
        *
        *   \param time The time elapsed since the last update
        */
        void update (float time);

        /*!
        *   \brief Create a physical dynamic box
        *
        *   \param xPosition The x position of the box
        *   \param yPosition The y position of the box
        *   \param xSize The width of the box
        *   \param ySize The height of the box
        *
        *   \return A pointer on a b2Body object
        */
        b2Body* addBox (float xPosition, float yPosition, float xSize, float ySize);

        /*!
        *   \brief Create a physical static box
        *
        *   \param xPosition The x position of the box
        *   \param yPosition The y position of the box
        *   \param xSize The width of the box
        *   \param ySize The height of the box
        *
        *   \return A pointer on a b2Body object
        */
        b2Body* addStaticBox (float xPosition, float yPosition, float xSize, float ySize);

        /*!
        *   \brief Create a physical dynamic circle
        *
        *   \param xPosition The x position of the circle
        *   \param yPosition The y position of the circle
        *   \param radius The radius of the circle
        *
        *   \return A pointer on a b2Body object
        */
        b2Body* addCircle (float xPosition, float yPosition, float radius);

        /*!
        *   \brief Create a physical static edge (not implemented yet)
        *
        *   \param xFirstPosition The x position of the first point of the edge
        *   \param yFirstPosition The y position of the first point of the edge
        *   \param xSecondPosition The x position of the second point of the edge
        *   \param ySecondPosition The y position of the second point of the edge
        *
        *   \return A pointer on a b2Body object
        */
        b2Body* addEdge (float xFirstPosition, float yFirstPosition, float xSecondPosition, float ySecondPosition);

        /*!
        *   \brief Create a physical static chain (multiple edges)
        *
        *   \param vpCoord A vector of pair of coordinates for each point of the chain
        *
        *   \return A pointer on a b2Body object
        */
        b2Body* addChainShape (std::vector<std::pair<float,float> > vpCoord);

        /*!
        *   \brief Get a pointer of the current world
        *
        *   \return A pointer on a b2World
        */
        b2World* getWorld();

    protected :

        PhyEngine ();               //!< Constructor
        ~PhyEngine();               //!< Destructor

        b2World* m_b2World;         //!< A Box2D world which will contain the physical scene

        int velocityIterations;
        int positionIterations;

};

#endif // PHYENGINE_HPP_INCLUDED
