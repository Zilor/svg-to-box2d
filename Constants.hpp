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

#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED

// Tinyxml
#include "dependency/tinyxml/tinyxml.h"

// Box2d
#include "Box2D.h"

// SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


// STL
#include <iostream>
#include <vector>
#include <algorithm>

const float PI = acos(-1.0);


// Object data from the SVG parsing
struct RectData
{
    float xPosition;
    float yPosition;
    float xSize;
    float ySize;
};

struct CircleData
{
    float xPosition;
    float yPosition;
    float radius;
};

struct LineData
{
    std::vector<std::pair<float,float> > vpCoord;
};

struct ObjectData
{
    std::vector<RectData*> vRectData;
    std::vector<CircleData*> vCircleData;
    std::vector<LineData*> vLineData;
};

// Foncteur servant à libérer un pointeur - applicable à n'importe quel type
struct Delete
{
   template <class T> void operator ()(T*& p) const
   {
      delete p;
      p = NULL;
   }
};


// Include of singletons to use them everywhere
#include "include/PhyEngine.hpp"
#include "include/GraphicEngine.hpp"
#include "include/SVGParser.hpp"


#endif // CONSTANTS_HPP_INCLUDED
