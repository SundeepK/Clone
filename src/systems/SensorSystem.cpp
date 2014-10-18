#include <systems/SensorSystem.h>
#include <components/SensorComponent.h>

class SensorSystem::SensorSystemImpl {

public:
	SensorSystemImpl(){
	}

	~SensorSystemImpl(){
	}

	void incrementSensor(b2Contact* contact, std::vector<anax::Entity> entities){
		for(auto entity : entities){
			auto& sensorComp = entity.getComponent<SensorComponent>();
				if(sensorComp.sensors == contact->m_fixtureA || sensorComp.sensors == contact->m_fixtureB){
					sensorComp.currentTotalContacts++;
				}
		}
	}

	void decrementSensor(b2Contact* contact, std::vector<anax::Entity> entities){
		for(auto entity : entities){
			auto& sensorComp = entity.getComponent<SensorComponent>();
				if(sensorComp.sensors == contact->m_fixtureA || sensorComp.sensors == contact->m_fixtureB){
					sensorComp.currentTotalContacts--;
				}
		}
	}

};

SensorSystem::SensorSystem() : Base(anax::ComponentFilter().requires<SensorComponent>()), m_impl(new SensorSystemImpl()){
}

SensorSystem::~SensorSystem() {
}

void SensorSystem::BeginContact(b2Contact* contact) {
	auto entities = getEntities();
	m_impl->incrementSensor(contact, entities);
}

void SensorSystem::EndContact(b2Contact* contact) {
	auto entities = getEntities();
	m_impl->decrementSensor(contact, entities);
}
