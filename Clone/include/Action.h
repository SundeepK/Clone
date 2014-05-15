#ifndef ACTION_H
#define ACTION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "LogicalNode.h"

class Action
{
    public:
        Action();
        virtual ~Action();

    protected:
    private:
        Action m_linkedNode;
        sf::Event
};

#endif // ACTION_H
