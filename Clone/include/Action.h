#ifndef ACTION_H
#define ACTION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "EventNode.h"
#include "RealtimeAndNode.h"
#include "AndEventNode.h"
#include <memory>

enum ActionType {
    RealTime,
    Event
};


class Action
{
    public:
        Action();
        Action(sf::Keyboard::Key key, ActionType actionType = RealTime );
        virtual ~Action();
        Action operator&& (const Action& lhs);
        bool isActionTriggered(std::vector<sf::Event>& events);
    protected:
    private:
        Action(EventNode* nextEvent);
        std::shared_ptr<EventNode> m_linkedNode;
};

#endif // ACTION_H
