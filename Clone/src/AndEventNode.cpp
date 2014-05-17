#include "AndEventNode.h"

AndEventNode::AndEventNode(sf::Keyboard event, EventNode* nextNode)
{
}

AndEventNode::~AndEventNode()
{
}


EventNode* AndEventNode::getNode(){
    return m_nextNode.get();
}

void AndEventNode::setNextNode(EventNode* nextNode){

}
