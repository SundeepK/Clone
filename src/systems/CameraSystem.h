#ifndef CAMERASYSTEM_H_
#define CAMERASYSTEM_H_

#include <anax/System.hpp>
#include <SFML/Graphics.hpp>
#include <components/PlayerStateComponent.h>
#include <components/PhysicsComponent.h>


class CameraSystem : public sf::Drawable, public anax::System<CameraSystem>{
	public:
		CameraSystem();
		virtual ~CameraSystem();
		void update();

	private:
		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
		sf::View m_view;

};

#endif /* CAMERASYSTEM_H_ */
