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
        AndEventNode(sf::Keyboard event, EventNode* nextNode);
        virtual ~AndEventNode();
        EventNode* getNode();
        void setNextNode(EventNode* nextNode);
    protected:
    private:
        sf::Keyboard m_event;
        std::unique_ptr<EventNode> m_nextNode;
};

#endif // ANDEVENTNODE_H
