#include <systems/DetectLevelEndSystem.h>
#include <vector>
#include <components/SensorComponent.h>
#include <components/Sensors.h>
#include <components/PlayerTagComponent.h>
#include <components/EndPointCollisionTagComponent.h>
#include <components/EndPointTagComponent.h>
#include <iostream>

class DetectLevelEndSystem::DetectLevelEndSystemImpl{

public:

	std::unique_ptr<TmxBox2dLevelLoader> m_tmxLevelLoader;

	DetectLevelEndSystemImpl(TmxBox2dLevelLoader& tmxMapLoader) : m_tmxLevelLoader(&tmxMapLoader){

	}

	~DetectLevelEndSystemImpl(){

	}

	void processLevelEndCollision(std::vector<anax::Entity>& entities){
		anax::Entity playerEntity;
		anax::Entity endPointEntity;
		for (auto entity : entities) {
			if(entity.hasComponent<PlayerTagComponent>()){
				playerEntity = entity;
			}else if(entity.hasComponent<EndPointTagComponent>()){
				endPointEntity = entity;
			}
			if( playerEntity.getId() > 0 && endPointEntity.getId() > 0 ){
				//id 0 is default id for entities
				break;
			}
		}

		auto & footSensor = playerEntity.getComponent<Sensor>().sensors["FootSensor"];
		auto & rightSensor = playerEntity.getComponent<Sensor>().sensors["RightSensor"];
		auto & leftSensor = playerEntity.getComponent<Sensor>().sensors["LeftSensor"];
		auto & endPointSensor = endPointEntity.getComponent<Sensor>().sensors["EndPointSensor"];

		if((footSensor.currentTotalContacts >= 1 || rightSensor.currentTotalContacts >= 1  || leftSensor.currentTotalContacts >= 1 ) && endPointSensor.currentTotalContacts >= 1){
			m_tmxLevelLoader->loadNextLevel();
		}
	}


};


DetectLevelEndSystem::DetectLevelEndSystem(TmxBox2dLevelLoader& tmxMapLoader) :  Base(anax::ComponentFilter().requires<Sensor, EndPointCollisionTagComponent>()), m_impl(new DetectLevelEndSystemImpl(tmxMapLoader)) {

}

DetectLevelEndSystem::~DetectLevelEndSystem() {
}

void DetectLevelEndSystem::processEndLevel() {
	auto entites = getEntities();
	m_impl->processLevelEndCollision(entites);
}
