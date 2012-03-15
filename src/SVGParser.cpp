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

/*!
*   \file SVGParser.cpp
*   \brief The SVG parser source
*   \version 0.1
*   \author Bastien (Bigz) Cramillet
*/

#include "../include/SVGParser.hpp"

SVGParser::SVGParser ()
{

}

SVGParser::~SVGParser ()
{
    if (!m_objectData.vRectData.empty())
    {
        std::for_each(m_objectData.vRectData.begin(), m_objectData.vRectData.end(), Delete());
        std::for_each(m_objectData.vCircleData.begin(), m_objectData.vCircleData.end(), Delete());
        std::for_each(m_objectData.vLineData.begin(), m_objectData.vLineData.end(), Delete());
    }
}

ObjectData& SVGParser::parse (std::string sFile)
{
    // Loading of the SVG file
    TiXmlDocument doc(sFile.c_str());
    if ( ! doc.LoadFile() )
    {
        std::cerr << "error during loading of the following file :" << std::endl;
        std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
    }


    TiXmlHandle hdl(&doc);


    TiXmlElement *object = hdl.FirstChildElement("svg").
                            Element();

    // If it's a .svg in complex mode
    if (object->FirstChildElement("sodipodi:namedview"))
    {
        // Let's parse the rectangle objects
        object = hdl.FirstChildElement("svg").
                            FirstChildElement("g").
                            FirstChildElement("rect").
                            Element();

            for (object; object; object = object->NextSiblingElement())
            {
                RectData* rectData = new RectData;

                rectData->xPosition = (atoi( object->Attribute("x") ) + (atoi( object->Attribute("width") ) / 2.f));
                rectData->yPosition = (atoi( object->Attribute("y") ) + (atoi( object->Attribute("height") ) / 2.f));
                rectData->xSize = atoi( object->Attribute("width") );
                rectData->ySize = atoi (object->Attribute("height") );

                m_objectData.vRectData.push_back(rectData);
            }

        object = hdl.FirstChildElement("svg").
                            FirstChildElement("g").
                            FirstChildElement("path").
                            Element();

            for (object; object; object = object->NextSiblingElement())
            {
                // If it's a circle
                if (object->Attribute("sodipodi:type"))
                {
                    CircleData * circleData = new CircleData;

                    circleData->xPosition = atoi( object->Attribute("sodipodi:cx") );
                    circleData->yPosition = atoi( object->Attribute("sodipodi:cy") );
                    circleData->radius = atoi( object->Attribute("sodipodi:rx") );

                    m_objectData.vCircleData.push_back(circleData);
                }
                // If it's a polyline
                else if (object->Attribute("d"))
                {
                    LineData* lineData = new LineData;

                    std::string currentString = "";
                    std::string currentChar = "";
                    std::string X = "";
                    std::string Y = "";
                    std::string stringToParse = object->Attribute("d");
                    std::string::iterator it = stringToParse.begin();

                    bool relative = true;


                    std::vector<std::pair<float, float> > vpCoord;

                    while (it != stringToParse.end())
                    {
                        currentChar = *it;

                        if (currentChar == "M")
                        {
                            relative = false;
                            currentString = "";
                        }
                        else if (currentChar == "l")
                        {
                            relative = true;
                        }
                        else if (currentChar == "L")
                        {
                            relative = false;
                        }
                        else if (currentChar == ",")
                        {
                            X = currentString;
                            currentString = "";
                        }
                        else if (currentChar == " " && X != "")
                        {
                            Y = currentString;
                            if (!relative || vpCoord.empty())
                            {
                                std::pair<float,float> pair(atof(X.c_str()), atof(Y.c_str()));
                                vpCoord.push_back(pair);
                            }
                            else
                            {
                                float oldX = vpCoord.back().first;
                                float oldY = vpCoord.back().second;

                                float absoluteX = atof(X.c_str()) + oldX;
                                float absoluteY = atof(Y.c_str()) + oldY;

                                std::pair<float,float> pair(absoluteX, absoluteY);
                                vpCoord.push_back(pair);

                            }
                            currentString = "";
                            X = "";
                            Y = "";
                        }
                        else if (currentChar == " " && X != "" && Y != "")
                        {
                            X = "";
                            Y = "";
                        }
                        else
                        {
                            currentString += *it;
                        }
                        it++;
                    }

                    for (int i = 0; i < vpCoord.size(); ++i)
                    {
                        std::cout << "X : " << vpCoord[i].first << "  Y : " << vpCoord[i].second << std::endl;
                    }

                    lineData->vpCoord = vpCoord;

                    m_objectData.vLineData.push_back(lineData);
                }
            }
    }
    // If it's a .svg in simple mode
    else
    {
        // Let's parse the rectangle objects
        object = hdl.FirstChildElement("svg").
                            FirstChildElement("g").
                            FirstChildElement("rect").
                            Element();

            for (object; object; object = object->NextSiblingElement())
            {
                RectData* rectData = new RectData;

                rectData->xPosition = (atoi( object->Attribute("x") ) + (atoi( object->Attribute("width") ) / 2.f));
                rectData->yPosition = (atoi( object->Attribute("y") ) + (atoi( object->Attribute("height") ) / 2.f));
                rectData->xSize = atoi( object->Attribute("width") );
                rectData->ySize = atoi (object->Attribute("height") );

                m_objectData.vRectData.push_back(rectData);
            }
    }





            delete object;

    return m_objectData;
}
