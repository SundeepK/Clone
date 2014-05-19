#include "ActionController.h"
//
//template <typename Key_type>
//ActionController<Key_type>::ActionController()
//{
//}
//
//template <typename Key_type>
//ActionController<Key_type>::ActionController(ActionController&& source)
//: m_events(std::move(source.m_events))
//, m_keyToActions(std::move(source.m_keyToActions))
//{
//}
//
//
//
//template <typename Key_type>
//ActionController<Key_type>& ActionController<Key_type>::operator= (ActionController&& source)
//{
//	m_events = std::move(source.m_events);
//	m_keyToActions = std::move(source.m_keyToActions);
//
//	return *this;
//}
//
//template <typename Key_type>
//Action& ActionController<Key_type>::operator[] (const Key_type& actionKey)
//{
//    ActionToCallbacks actionsToCallbacks = m_keyToActions[actionKey];
//    if(actionsToCallbacks){
//      return m_keyToActions[actionKey].m_action;
//    }else{
//          ActionToCallbacks actCallbacks;
//          m_keyToActions[actionKey] =  actCallbacks;
//          return m_keyToActions[actionKey];
//    }
//}
//
////template <typename Key_type>
////ActionToCallbacks ActionController<Key_type>::operator[] (const Key_type& actionKey)
////{
////    return m_keyToActions[actionKey];
////}
//
//template <typename Key_type>
//void ActionController<Key_type>::update(sf::RenderWindow& window)
//{
//    sf::Event event;
//    while (window.pollEvent(event))
//    {
//        if (event.type == sf::Event::Closed)
//        {
//            window.close();
//        }
//        m_events.push_back(event);
//    }
//
//}
//
//template <typename Key_type>
//void ActionController<Key_type>::triggerCallbacks()
//{
//    for ( auto actionItr = m_keyToActions.begin(); actionItr!= m_keyToActions.end(); ++actionItr )
//    {
//        ActionToCallbacks actionsToCallbacks = actionItr->second;
//        Action action = actionsToCallbacks.m_action;
//        if(action.isActionTriggered(m_events))
//        {
//            auto callbacks = actionsToCallbacks.m_callbacks;
//            for(auto && fn : callbacks)
//                fn();
//        }
//    }
//    m_events.clear();
//}
