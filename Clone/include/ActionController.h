#ifndef EVENCONTROLLER_H
#define EVENCONTROLLER_H

#include <unordered_map>
#include "Action.h"
#include <vector>

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
        Action& operator[] (const Key_type& actionKey);
        void addCallback(const Key_type&, std::function<void()> callback);
    protected:
    private:
        std::unordered_map<const Key_type, Action, TemplateHasher<Key_type>> m_keyToActions;
};

#endif // EVENCONTROLLER_H
