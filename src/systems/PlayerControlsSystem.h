#ifndef PLAYERCONTROLSSYSTEM_H_
#define PLAYERCONTROLSSYSTEM_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <anax/System.hpp>
#include <memory>


class PlayerControlsSystem : public anax::System<PlayerControlsSystem> {


	public:
		PlayerControlsSystem();
	//	PlayerControlsSystem(std::unordered_map<PlayerState, sf::Keyboard::Key, std::hash<int>> playerControlsMap);
		~PlayerControlsSystem();
		void update(sf::RenderWindow& window, float dt);

	private:

		class PlayerControlsSystemImpl;
		std::unique_ptr<PlayerControlsSystemImpl> m_impl;

};

#endif /* PLAYERCONTROLSSYSTEM_H_ */
