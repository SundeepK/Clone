#include "Action.h"

Action::Action(sf::Keyboard::Key key)
{
}

Action::~Action()
{
}

Action& Action::operator&& (const Action& lhs)
{
    EventNode* node = m_linkedNode.get();
    while(node){
        node = node->getNode();
    }
    node->setNextNode(lhs.m_linkedNode.get());
	return *this;
}

bool Action::isActionTriggered(std::vector<sf::Event>& events ){
  return  m_linkedNode->applyPredicateToEvents(events);
}
