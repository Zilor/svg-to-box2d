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

#include "../Constants.hpp"
#include "Singleton.hpp"

class PhyEngine : public Singleton<PhyEngine>
{
    friend class Singleton<PhyEngine>;

    public :

        void init ();

        void update (float time);

        b2Body* addBox (float xPosition, float yPosition, float xSize, float ySize);

        b2Body* addStaticBox (float xPosition, float yPosition, float xSize, float ySize);

        b2Body* addCircle (float xPosition, float yPosition, float radius);

        b2Body* addEdge (float xFirstPosition, float yFirstPosition, float xSecondPosition, float ySecondPosition);

        b2Body* addChainShape (std::vector<std::pair<float,float> > vpCoord);

        b2World* getWorld();

    protected :

        PhyEngine ();

        b2World* m_b2World;

        int velocityIterations;
        int positionIterations;

};

#endif // PHYENGINE_HPP_INCLUDED
