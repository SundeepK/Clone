#ifndef CAMERASYSTEM_H_
#define CAMERASYSTEM_H_

#include <anax/System.hpp>
#include <SFML/Graphics.hpp>
#include <Vec.h>
#include <components/PhysicsComponent.h>
#include <components/PlayerTagComponent.h>


class CameraSystem : public sf::Drawable, public anax::System<CameraSystem>{
	public:
		CameraSystem(int width, int height);
		virtual ~CameraSystem();
		void update();

	private:
		int m_screenWidth;
		int m_screenHeight;
		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
		sf::View m_view;

};

#endif /* CAMERASYSTEM_H_ */
