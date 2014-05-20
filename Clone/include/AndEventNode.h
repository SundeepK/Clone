#ifndef ANDEVENTNODE_H
#define ANDEVENTNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "EventNode.h"

class AndEventNode : public EventNode
{
    public:
        AndEventNode(sf::Keyboard::Key event, EventNode* nextNode);
        virtual ~AndEventNode();
        EventNode* getNode();
        void setNextNode(EventNode* nextNode);
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

    protected:
    private:
        sf::Keyboard::Key m_event;
        std::shared_ptr<EventNode> m_nextNode;
};

#endif // ANDEVENTNODE_H
