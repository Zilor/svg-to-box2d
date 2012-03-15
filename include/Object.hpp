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

#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

/*!
*   \file Object.hpp
*   \brief The object class header
*   \version 0.1
*   \author Bastien (Bigz) Cramillet
*/


#include "../Constants.hpp"

class Drawable;
class b2Body;
class Screen;

/*!
*   \class Object
*   \brief A dynamic object composed of a SFML drawable object and a physical Box2D object
*/

class Object
{
    public :

        /*!
        *   \brief Constructor
        */
        Object ();

        /*!
        *   \brief Destructor
        */
        ~Object ();

        /*!
        *   \brief Getter on the Drawable object
        *
        *   \return A pointer on a sf:Drawable
        */
        const sf::Drawable* getDrawable() const;

        void setBody (b2Body* body);
        void setDrawable (sf::Drawable* drawable);
        void setType (PHYSIC_TYPE type);

        /*!
        *   \brief update the position of the object
        */
        void update ();

        /*!
        *   \brief Draw the object on the given render target
        *
        *   \param screen The render target on which the object should be draw
        */
        void draw (Screen& screen);


    private :

        b2Body* m_body;             //!< A pointer to the physical object bounded to this object
        sf::Drawable* m_drawable;   //!< A pointer to the drawable object bounded to this object
        PHYSIC_TYPE m_type;         //!< A flag to define if the position of the drawalbe should be updated

};



#endif // OBJECT_HPP_INCLUDED
