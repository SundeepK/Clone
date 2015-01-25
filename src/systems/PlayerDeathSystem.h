#ifndef SRC_SYSTEMS_PLAYERDEATHSYSTEM_H_
#define SRC_SYSTEMS_PLAYERDEATHSYSTEM_H_

#include <anax/System.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <Box2D/Box2D.h>

class PlayerDeathSystem :  public b2ContactListener,  public anax::System<PlayerDeathSystem> {
public:
	PlayerDeathSystem();
	~PlayerDeathSystem();

	void update(sf::Vector2u mapSize);
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);


private:
	class PlayerDeathSystemImpl;
	std::unique_ptr<PlayerDeathSystemImpl> m_impl;
};

#endif /* SRC_SYSTEMS_PLAYERDEATHSYSTEM_H_ */
