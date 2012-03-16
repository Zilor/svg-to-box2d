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
*   \file Object.cpp
*   \brief The object source
*   \version 0.1
*   \author Bastien (Bigz) Cramillet
*/

#include "../include/Object.hpp"
#include "../include/Screen.hpp"

Object::Object ()
{
    m_body = NULL;
    m_drawable = NULL;
}

Object::~Object ()
{
    m_body = NULL;
    m_drawable = NULL;
}

const sf::Drawable* Object::getDrawable () const
{
    return m_drawable;
}

void Object::setBody(b2Body* body)
{
    if (!m_body)
    {
        m_body = body;
    }
}

void Object::setDrawable(sf::Drawable* drawable)
{
    if (!m_drawable)
    {
        m_drawable = drawable;
    }
}

void Object::setType (PHYSIC_TYPE type)
{
    m_type = type;
}

void Object::update ()
{
    if (m_type == DYNAMIC)
    {
        dynamic_cast<sf::Transformable*>(m_drawable)->setPosition((m_body->GetPosition().x * 100.f), (m_body->GetPosition().y * 100.f));
        dynamic_cast<sf::Transformable*>(m_drawable)->setRotation(m_body->GetAngle() * 180.f / PI);
    }
}

void Object::draw (Screen& screen)
{
    screen.draw(*m_drawable);
}
