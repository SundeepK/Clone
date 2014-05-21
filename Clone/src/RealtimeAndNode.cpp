#include "RealtimeAndNode.h"

RealtimeAndNode::RealtimeAndNode(sf::Keyboard::Key event, EventNode* nextNode) :  m_event(event), m_nextNode(nextNode)
{
}

RealtimeAndNode::~RealtimeAndNode()
{
}


EventNode* RealtimeAndNode::getNode(){
    return m_nextNode.get();
}

void RealtimeAndNode::setNextNode(EventNode* nextNode){
    m_nextNode.reset(nextNode);
}

bool RealtimeAndNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    bool eventTriggered =  sf::Keyboard::isKeyPressed(m_event);
    if(m_nextNode){
       return eventTriggered && m_nextNode->isEventTriggered(keyboardEvents);
    }else{
        return eventTriggered;
    }
}
