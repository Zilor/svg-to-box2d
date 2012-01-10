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

#include "../include/Scene.hpp"
#include "../include/Object.hpp"

Scene::Scene ()
{
    addStaticRect(512, 768, 1024, 100);
}

Scene::~Scene ()
{
    if (!m_vObject.empty())
    {
        std::for_each(m_vObject.begin(), m_vObject.end(), Delete());
    }
}

const std::vector<Object*>& Scene::GetVObject() const
{
    return m_vObject;
}

Object Scene::GetObject (int i)
{
    return *m_vObject[i];
}

void Scene::update ()
{
    int size = m_vObject.size();
    for (int i = 0; i < size; ++i)
    {
        m_vObject[i]->update();
    }
}

void Scene::draw (Screen& screen)
{
    int size = m_vObject.size();
    for (int i = 0; i < size; ++i)
    {
        m_vObject[i]->draw(screen);
    }
}

void Scene::createFromFile(std::string sFile)
{
    // Parsing of the svg file
    ObjectData objectData = SVGParser::getInstance()->parse(sFile);

    // Let's create all the rectangles
    if (!objectData.vRectData.empty())
    {
        int nvRectSize = objectData.vRectData.size();
        for (int i = 0; i < nvRectSize; ++i)
        {
            // Using its own function to create rectangle
            addRect(
                    objectData.vRectData[i]->xPosition,
                    objectData.vRectData[i]->yPosition,
                    objectData.vRectData[i]->xSize,
                    objectData.vRectData[i]->ySize
                    );
        }
    }
    if (!objectData.vCircleData.empty())
    {
        int nvCircleSize = objectData.vCircleData.size();
        for (int i = 0; i < nvCircleSize; ++i)
        {
            addCircle(
                      objectData.vCircleData[i]->xPosition,
                      objectData.vCircleData[i]->yPosition,
                      objectData.vCircleData[i]->radius
                      );
        }
    }
    if (!objectData.vLineData.empty())
    {
        int nvLineSize = objectData.vLineData.size();
        for (int i = 0; i < nvLineSize; ++i)
        {
            addLine(objectData.vLineData[i]->vpCoord);
        }
    }
}

void Scene::addRect(float xPosition, float yPosition, float xSize, float ySize)
{
    // We create a new object
    Object* object = new Object();
    // We ask to the physic engine to create a b2Body
    object->SetBody(PhyEngine::getInstance()->addBox(
                                                     xPosition,
                                                     yPosition,
                                                     xSize,
                                                     ySize)
                    );

    // We ask to the graphic engine to create a drawable shape
    object->SetDrawable(GraphicEngine::getInstance()->addBoxDrawable(
                                                                 xPosition,
                                                                 yPosition,
                                                                 xSize,
                                                                 ySize)
                      );

    // Let's add this object to the list of objects of the list
    m_vObject.push_back(object);
}

void Scene::addStaticRect(float xPosition, float yPosition, float xSize, float ySize)
{
    Object* object = new Object();
    object->SetBody(PhyEngine::getInstance()->addStaticBox(
                                                     xPosition,
                                                     yPosition,
                                                     xSize,
                                                     ySize)
                    );

    object->SetDrawable(GraphicEngine::getInstance()->addStaticBoxDrawable(
                                                                 xPosition,
                                                                 yPosition,
                                                                 xSize,
                                                                 ySize)
                      );

    m_vObject.push_back(object);
}

void Scene::addCircle (float xPosition, float yPosition, float radius)
{
    Object* object = new Object();
    object->SetBody(PhyEngine::getInstance()->addCircle(
                                                     xPosition,
                                                     yPosition,
                                                     radius)
                    );

    object->SetDrawable(GraphicEngine::getInstance()->addCircleDrawable(
                                                                 xPosition,
                                                                 yPosition,
                                                                 radius)
                      );


    m_vObject.push_back(object);
}

void Scene::addLine (std::vector<std::pair<float, float> > vpCoord)
{
    Object* object = new Object();
    object->SetBody(PhyEngine::getInstance()->addChainShape(vpCoord));
    object->SetDrawable(GraphicEngine::getInstance()->addStaticPolyline(vpCoord));

    m_vObject.push_back(object);
}
