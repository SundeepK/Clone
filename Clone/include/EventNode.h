#ifndef LOGICALNODE_H
#define LOGICALNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>

class EventNode
{
    public:
        EventNode();
        virtual ~EventNode();
        virtual bool isEventTriggered(std::vector<sf::Event>& keyboardEvents) = 0;
        virtual EventNode* getNode() = 0;
        virtual void setNextNode(EventNode* nextNode) = 0;
    protected:
    private:
};


#endif // LOGICALNODE_H
