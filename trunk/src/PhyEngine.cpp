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

#include "../include/PhyEngine.hpp"
#include <SFML/System.hpp>

PhyEngine::PhyEngine ()
{
    init();
}

PhyEngine::~PhyEngine ()
{
    clear();
}

void PhyEngine::clear ()
{
    if (m_b2World != NULL)
    {
        delete m_b2World;
        m_b2World = NULL;
    }
}

void PhyEngine::init()
{
    if (m_b2World == NULL)
    {
        b2Vec2 gravity(0.0f, 9.8f);                     // Gravity of the world
        m_b2World = new b2World(gravity);       // v2.2.1
        m_b2World->SetAllowSleeping(true);   // Stop to calculate movement for non-moving objects
        velocityIterations = 8;     // If your machine is powerfull enough, this is the best configuration
        positionIterations = 3;
    }
}

void PhyEngine::update (float time)
{
    // Update the world
    m_b2World->Step(0.01, velocityIterations, positionIterations);
    m_b2World->ClearForces();
}

b2Body* PhyEngine::addBox(float xPosition, float yPosition, float xSize, float ySize)
{
	// Creation of a dynamic rectangle
    b2BodyDef bodyDef;                              // Declaration of the body
    bodyDef.type = b2_dynamicBody;                  // Set the body as a dynamic one
    bodyDef.position.Set(xPosition / 100.f,
                         yPosition / 100.f);        // Set the body position
    bodyDef.angle = 0.f;                            // Set the body angle
    b2Body* body = m_b2World->CreateBody(&bodyDef); // We ask to the body factory to create it

    b2PolygonShape dynamicBox;                      // Declaration of the shape
    dynamicBox.SetAsBox((xSize / 200.f) - 0.01,
                        (ySize / 200.f) - 0.01);    // Set the size and the shape as a box

    b2FixtureDef fixtureDef;                        // We create a new fixture for the body
    fixtureDef.shape = &dynamicBox;                 // We attach the shape of the body to the fixture
    fixtureDef.density = 1.0f;                      // We set the density of the shape
    fixtureDef.friction = 0.3f;                     // We set the friction of the shape
    fixtureDef.restitution = 0.3f;                  // We set the restitution of the shape

    body->CreateFixture(&fixtureDef);               // We link the fixture to the body

    return body;
}

b2Body* PhyEngine::addStaticBox(float xPosition, float yPosition, float xSize, float ySize)
{
	// Creation of a static rectangle
    b2BodyDef bodyDef;                          // On déclare le body
    bodyDef.position.Set(xPosition / 100.f,
                         yPosition / 100.f);           // Position du corps
    bodyDef.angle = 0.f;                        // On donne un peu d'angle pour la simulation
    b2Body* body = m_b2World->CreateBody(&bodyDef);  // On demande au body factory de créer le body

    b2PolygonShape dynamicBox;                  // On déclare le shape du body
    dynamicBox.SetAsBox((xSize / 200.f) - 0.01,
                        (ySize / 200.f) - 0.01);            // On définit la taille et la forme en cube du shape

    b2FixtureDef fixtureDef;                    // On déclaire la fixture du body
    fixtureDef.shape = &dynamicBox;             // On applique le shape à la fixture
    fixtureDef.density = 1.0f;                  // On définit la densité de notre body
    fixtureDef.friction = 0.3f;                 // On définit la friction de notre body

    body->CreateFixture(&fixtureDef);           // On associe la fixture à notre body

    return body;
}


b2Body* PhyEngine::addCircle (float xPosition, float yPosition, float radius)
{
    // Création d'un objet dynamique : un simple cube qui tombe
    b2BodyDef bodyDef;                          // On déclare le body
    bodyDef.type = b2_dynamicBody;              // Le corps est dynamique
    bodyDef.position.Set(xPosition / 100.f,
                         yPosition / 100.f);           // Position du corps
    bodyDef.angle = 0.f;                        // On donne un peu d'angle pour la simulation
    b2Body* body = m_b2World->CreateBody(&bodyDef);  // On demande au body factory de créer le body

    b2CircleShape dynamicCircle;                  // On déclare le shape du body
    dynamicCircle.m_radius = radius / 100.f;

    b2FixtureDef fixtureDef;                    // On déclaire la fixture du body
    fixtureDef.shape = &dynamicCircle;             // On applique le shape à la fixture
    fixtureDef.density = 1.0f;                  // On définit la densité de notre body
    fixtureDef.friction = 0.3f;                 // On définit la friction de notre body
    fixtureDef.restitution = 0.3f;

    body->CreateFixture(&fixtureDef);           // On associe la fixture à notre body


    return body;
}

b2Body* PhyEngine::addEdge (float xFirstPosition, float yFirstPosition, float xSecondPosition, float ySecondPosition)
{

}

b2Body* PhyEngine::addChainShape (std::vector<std::pair<float,float> > vpCoord)
{
    int size = vpCoord.size();
    b2Vec2 vCoord[size];
    for (int i = 0; i < size; ++i)
    {
        vCoord[i].Set(vpCoord[i].first / 100.f,
                      vpCoord[i].second / 100.f);
    }

    // Création d'un objet dynamique : un simple cube qui tombe
    b2BodyDef bodyDef;                          // On déclare le body
    //bodyDef.position.Set(xPosition / 100.f, yPosition / 100.f);           // Position du corps
    bodyDef.angle = 0.f;                        // On donne un peu d'angle pour la simulation
    b2Body* body = m_b2World->CreateBody(&bodyDef);  // On demande au body factory de créer le body

    b2ChainShape staticChain;                  // On déclare le shape du body
    staticChain.CreateChain(vCoord, size);

    b2FixtureDef fixtureDef;                    // On déclaire la fixture du body
    fixtureDef.shape = &staticChain;             // On applique le shape à la fixture
    fixtureDef.density = 1.0f;                  // On définit la densité de notre body
    fixtureDef.friction = 0.3f;                 // On définit la friction de notre body

    body->CreateFixture(&fixtureDef);           // On associe la fixture à notre body

    return body;
}

b2World* PhyEngine::getWorld()
{
    return m_b2World;
}
