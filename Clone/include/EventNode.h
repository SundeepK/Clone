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

        virtual bool applyPredicateToEvents(std::vector<sf::Event>& keyboardEvents) = 0;
        virtual EventNode* getNode() = 0;
        virtual void setNextNode(EventNode* nextNode) = 0;
    protected:
    private:


};

#endif // LOGICALNODE_H
