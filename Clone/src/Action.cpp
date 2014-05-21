#include "Action.h"

Action::Action()
{
}


Action::Action(sf::Keyboard::Key key, ActionType actionType)
{
    switch(actionType){
        case RealTime:
            m_linkedNode.reset(new RealtimeAndNode(key, NULL));
            break;
        case Event:
            m_linkedNode.reset(new AndEventNode(key, NULL));
            break;
    }

}

Action::~Action()
{
}

Action::Action(EventNode* nextEvent){
    m_linkedNode.reset(nextEvent);
}


Action Action::operator&& (const Action& lhs)
{
    EventNode* node = m_linkedNode.get();
    while(node){
        EventNode* n = node->getNode();
        if(n){
           node = n;
        }else{
            break;
        }
    }
    EventNode* n1 = lhs.m_linkedNode.get();
    node->setNextNode(n1 );
	return Action(m_linkedNode.get());
}

bool Action::isActionTriggered(std::vector<sf::Event>& events ){
    return  m_linkedNode->isEventTriggered(events);
}
