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

#include "include/SVGParser.hpp"
#include "Constants.hpp"
#include "include/Screen.hpp"

// TODO (Bigz#1#): permettre de g�n�rer une nouvelle sc�ne apr�s avoir quitter la premi�re\

int main()
{
    std::string sAnswer = "";
    std::cout << "Which SVG file do you want to load ?" << std::endl;
    std::cin >> sAnswer;

    while (sAnswer != "/quit")
    {
        PhyEngine::getInstance()->init();

        Scene scene;
        if(scene.createFromFile(sAnswer))
        {
            Screen screen;
            screen.run(scene);

            SVGParser::getInstance()->clear();
            GraphicEngine::getInstance()->clear();
            PhyEngine::getInstance()->clear();
        }
        else
        {
            std::cout << "Impossible to parse this file" << std::endl;
        }

        std::cout << "Which SVG file do you want to load ?" << std::endl;
        std::cin >> sAnswer;
    }

    return EXIT_SUCCESS;
}
