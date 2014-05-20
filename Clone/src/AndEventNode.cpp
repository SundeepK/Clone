#include "AndEventNode.h"
#include <functional>

AndEventNode::AndEventNode(sf::Keyboard::Key event, EventNode* nextNode) :  m_event(event), m_nextNode(nextNode)
{
}

AndEventNode::~AndEventNode()
{
}


EventNode* AndEventNode::getNode(){
    return m_nextNode.get();
}

void AndEventNode::setNextNode(EventNode* nextNode){
    m_nextNode.reset(nextNode);
}

bool AndEventNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){

    bool found = std::find_if(keyboardEvents.begin(), keyboardEvents.end(), [this](const sf::Event& event) -> bool { return event.key.code == m_event;} ) != keyboardEvents.end();
    if(m_nextNode){
       return found && m_nextNode->isEventTriggered(keyboardEvents);
    }else{
        return found;
    }
}



