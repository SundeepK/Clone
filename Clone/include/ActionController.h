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

    void hash_combine(std::size_t & seed, const Key_type & v)
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
        virtual ~ActionController();
        ActionToCallbacks& operator[] (const Key_type& actionKey);
        void addCallback(const Key_type&, std::function<void()> callback);
        ActionController& operator= (ActionController&& controller);

        void update(sf::RenderWindow& window);
        void triggerCallbacks();
    protected:
    private:
        std::unordered_map<const Key_type, ActionToCallbacks, TemplateHasher<Key_type>> m_keyToActions;
        std::vector<sf::Event> m_events;

};

#endif // EVENCONTROLLER_H
