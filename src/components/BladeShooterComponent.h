#ifndef SRC_COMPONENTS_BLADESHOOTERCOMPONENT_H_
#define SRC_COMPONENTS_BLADESHOOTERCOMPONENT_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <vector>

enum BladeShooterState{
	NOT_STARTED,
	SHOOTING
};

class BladeShooterComponent : public anax::Component<BladeShooterComponent> {

public:

	b2Vec2 bladeLinerVelocty;
	b2Vec2 bladeSize;
	BladeShooterState bladeShooterState = BladeShooterState::NOT_STARTED;
	sf::Time lastTimeBladeShot;
	sf::Time delayBetweenBladeShots;
	sf::Time slowedDownAccumulation;
	std::vector<anax::Entity> previousBlades;

};

#endif /* SRC_COMPONENTS_BLADESHOOTERCOMPONENT_H_ */
