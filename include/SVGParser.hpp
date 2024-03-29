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

#ifndef SVGPARSER_HPP_INCLUDED
#define SVGPARSER_HPP_INCLUDED

/*!
*   \file SVGParser.hpp
*   \brief The SVG parser header
*   \version 0.1
*   \author Bastien (Bigz) Cramillet
*/

#include "../Constants.hpp"
#include "Singleton.hpp"

class SVGParser : public Singleton<SVGParser>
{
    friend class Singleton<SVGParser>;

    public :

        void clear();
        ObjectData& getObjectData();
        bool parse (std::string sFile);

    protected :

        SVGParser ();
        ~SVGParser ();

        ObjectData m_objectData;

};

#endif // SVGPARSER_HPP_INCLUDED
