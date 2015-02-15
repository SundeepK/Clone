#ifndef SRC_SYSTEMS_DRAWSTATICAABBSYSTEM_H_
#define SRC_SYSTEMS_DRAWSTATICAABBSYSTEM_H_

#include <anax/System.hpp>
#include <memory.h>
#include <anax/World.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class DrawStaticAABBSystem :  public anax::System<DrawStaticAABBSystem>, public sf::Drawable {
public:
	DrawStaticAABBSystem();
	~DrawStaticAABBSystem();

	void updateAABBs();

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	class DrawStaticAABBSystemImpl;
	std::unique_ptr<DrawStaticAABBSystemImpl> m_impl;

};

#endif /* SRC_SYSTEMS_DRAWSTATICAABBSYSTEM_H_ */
