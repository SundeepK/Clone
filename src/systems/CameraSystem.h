#ifndef CAMERASYSTEM_H_
#define CAMERASYSTEM_H_

#include <anax/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>


class CameraSystem : public sf::Drawable, public anax::System<CameraSystem>{
	public:
		CameraSystem(int width, int height);
		~CameraSystem();
		void update(sf::RenderWindow& window, sf::Vector2u  mapSize);
		void updateOpenglCamera();
		sf::View getView();

	private:

		class CameraSystemImpl;

		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
		std::unique_ptr<CameraSystemImpl> m_impl;

};

#endif /* CAMERASYSTEM_H_ */
