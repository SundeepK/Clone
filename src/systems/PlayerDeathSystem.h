#ifndef SRC_SYSTEMS_PLAYERDEATHSYSTEM_H_
#define SRC_SYSTEMS_PLAYERDEATHSYSTEM_H_

#include <anax/System.hpp>
#include <SFML/System.hpp>
#include <memory>

class PlayerDeathSystem :  public anax::System<PlayerDeathSystem> {
public:
	PlayerDeathSystem();
	~PlayerDeathSystem();

	void update(sf::Vector2u mapSize);

private:
	class PlayerDeathSystemImpl;
	std::unique_ptr<PlayerDeathSystemImpl> m_impl;
};

#endif /* SRC_SYSTEMS_PLAYERDEATHSYSTEM_H_ */
