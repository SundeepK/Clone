#ifndef EVENCONTROLLER_H
#define EVENCONTROLLER_H

#include <unordered_map>
#include "Action.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

template <typename Key_type>
struct TemplateHasher : public std::unary_function<Key_type, std::size_t> {
public:
    std::size_t operator()(const Key_type & t) const
    {
      size_t seed = 0;
      hash_combine(seed, t);
      return seed;
    }

    void hash_combine(std::size_t & seed, const Key_type & v) const
    {
        std::hash<Key_type> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};

struct ActionToCallbacks{
    Action m_action;
    std::vector<std::function<void()>> m_callbacks;
};

template <typename Key_type>
class ActionController
{
    public:
        ActionController();
        ActionController(ActionController&& source);
        Action& operator[] (const Key_type& actionKey);
        void addCallback(const Key_type& actionKey, std::function<void()> callback);
        ActionController& operator= (ActionController&& controller);

        void update(sf::RenderWindow& window);
        void triggerCallbacks();
    protected:
    private:
        std::unordered_map<const Key_type, ActionToCallbacks, TemplateHasher<Key_type>> m_keyToActions;
        std::vector<sf::Event> m_events;

};


template <typename Key_type>
ActionController<Key_type>::ActionController()
{
}

template <typename Key_type>
ActionController<Key_type>::ActionController(ActionController&& source)
: m_events(std::move(source.m_events))
, m_keyToActions(std::move(source.m_keyToActions))
{
}



template <typename Key_type>
ActionController<Key_type>& ActionController<Key_type>::operator= (ActionController&& source)
{
	m_events = std::move(source.m_events);
	m_keyToActions = std::move(source.m_keyToActions);

	return *this;
}

template <typename Key_type>
Action& ActionController<Key_type>::operator[] (const Key_type& actionKey)
{
    ActionToCallbacks actionsToCallbacks = m_keyToActions[actionKey];
    if(&actionsToCallbacks.m_action != NULL){
      return m_keyToActions[actionKey].m_action;
    }else{
          ActionToCallbacks actCallbacks = {};
          m_keyToActions[actionKey] =  actCallbacks;
          return m_keyToActions[actionKey].m_action;
    }
}

template <typename Key_type>
void ActionController<Key_type>::addCallback(const Key_type& actionKey, std::function<void()> callback){

    ActionToCallbacks actionsToCallbacks = m_keyToActions[actionKey];
    if(&actionsToCallbacks.m_action != NULL){
       m_keyToActions[actionKey].m_callbacks.push_back(callback);
    }
}

template <typename Key_type>
void ActionController<Key_type>::update(sf::RenderWindow& window)
{
    m_events.clear();
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        	switch (event.type)
		{
			case sf::Event::GainedFocus:
				break;

			case sf::Event::LostFocus:
				break;
		}

        m_events.push_back(event);
    }

}

template <typename Key_type>
void ActionController<Key_type>::triggerCallbacks()
{
    for ( auto actionItr = m_keyToActions.begin(); actionItr!= m_keyToActions.end(); ++actionItr )
    {
        ActionToCallbacks actionsToCallbacks = actionItr->second;
        Action action = actionsToCallbacks.m_action;
        if(action.isActionTriggered(m_events))
        {
            auto callbacks = actionsToCallbacks.m_callbacks;
            for(auto && fn : callbacks)
                fn();
        }

    }
}
#endif // EVENCONTROLLER_H
