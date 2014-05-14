#ifndef KEYEVENTCONTROLLER_H
#define KEYEVENTCONTROLLER_H

#include <functional>
#include <vector>
#include <unordered_map>

class KeyEventController
{
    public:
        KeyEventController();
        virtual ~KeyEventController();
    protected:
    private:
       std::unordered_map<std::string, std::function<void()>> m_eventsToCallbacks;

};

#endif // KEYEVENTCONTROLLER_H
