#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player : public sf::Drawable
{
    public:
        Player();
        virtual ~Player();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
    private:
};

#endif // PLAYER_H
