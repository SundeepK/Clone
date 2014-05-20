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
       return sf::Keyboard::isKeyPressed(m_event) && m_nextNode->isEventTriggered(keyboardEvents);
}
