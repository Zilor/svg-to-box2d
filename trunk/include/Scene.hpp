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

#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "../Constants.hpp"

class Object;
class Screen;

class Scene
{
    public :

        Scene ();

        ~Scene ();

        void addRect (float xPosition, float yPosition, float xSize, float ySize);

        void addStaticRect (float xPosition, float yPosition, float xSize, float ySize);

        void addCircle (float xPosition, float yPosition, float radius);

        void addLine (std::vector<std::pair<float, float> > vpCoord);

        void createFromFile(std::string sFile);

        void update();

        void draw(Screen& screen);

        const std::vector<Object*>& GetVObject() const;

        Object GetObject(int i);

    private :

        std::vector<Object*> m_vObject;

};


#endif // SCENE_HPP_INCLUDED
