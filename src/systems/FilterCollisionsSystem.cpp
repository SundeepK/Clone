
#include <systems/FilterCollisionsSystem.h>
#include <anax/Entity.hpp>
#include <anax/World.hpp>
#include <components/IgnoreCollisionComponent.h>
#include <vector>
#include <SFML/System.hpp>
#include <iostream>
class FilterCollisionsSystem::FilterCollisionsSystemImpl{
public:
	sf::Clock m_clock;
	sf::Time m_maxIgnoreTime;

	FilterCollisionsSystemImpl() :  m_maxIgnoreTime(sf::milliseconds(500)){
	}

	~FilterCollisionsSystemImpl(){
	}

	void filterCollisions(std::vector<anax::Entity>& entities) {
		sf::Time currentTime = m_clock.getElapsedTime();
		for (auto entity : entities) {
			if (entity.isValid() &&  entity.hasComponent<IgnoreCollisionComponent>()) {
				auto& ignoreCollisionComp = entity.getComponent<IgnoreCollisionComponent>();
				if(ignoreCollisionComp.reason == IgnoreCollisionReason::NEW_SPLIT_BODY){
					if (currentTime - ignoreCollisionComp.timeIgnoreCollisionAdded >= m_maxIgnoreTime) {
						entity.removeComponent<IgnoreCollisionComponent>();
						//std::cout << "about to mark as deleted" << std::endl;
					}
				}
			}
		}
	}

};

FilterCollisionsSystem::FilterCollisionsSystem() : Base(anax::ComponentFilter().requires<IgnoreCollisionComponent>()), m_impl(new FilterCollisionsSystemImpl()) {

}

FilterCollisionsSystem::~FilterCollisionsSystem() {
}

void FilterCollisionsSystem::filterCollisions() {
	auto entities =	getEntities();
	m_impl->filterCollisions(entities);
}
