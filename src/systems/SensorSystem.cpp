#include <systems/SensorSystem.h>
#include <components/SensorComponent.h>
#include <components/Sensors.h>
#include <iostream>
#include <vector>

class SensorSystem::SensorSystemImpl {

public:

	std::vector<b2ContactListener*> m_listeners;


	SensorSystemImpl(){
	}

	~SensorSystemImpl(){
	}

	void incrementSensor(b2Contact* contact, std::vector<anax::Entity> entities){
		for (auto entity : entities) {
			auto& sensorComp = entity.getComponent<Sensor>().sensors;
			for(auto sensorItr=sensorComp.begin(); sensorItr!=sensorComp.end(); ++sensorItr) {
				if (sensorItr->second.sensors == contact->GetFixtureA()
						|| sensorItr->second.sensors == contact->GetFixtureB()) {
					sensorItr->second.currentTotalContacts++;
				}
			}
		}

		for(auto& listeners : m_listeners){
			listeners->BeginContact(contact);
		}
	}

	void decrementSensor(b2Contact* contact, std::vector<anax::Entity> entities){
		for (auto entity : entities) {
			auto& sensorComp = entity.getComponent<Sensor>().sensors;
			for(auto sensorItr=sensorComp.begin(); sensorItr!=sensorComp.end(); ++sensorItr) {
				if (sensorItr->second.sensors == contact->GetFixtureA()
						|| sensorItr->second.sensors == contact->GetFixtureB()) {
					sensorItr->second.currentTotalContacts--;
				}
			}
		}

		for(auto& listeners : m_listeners){
			listeners->EndContact(contact);
		}
	}

	void registerb2ContactListener(b2ContactListener* listener){
		m_listeners.push_back(listener);
	}

};

SensorSystem::SensorSystem() : Base(anax::ComponentFilter().requires<Sensor>()), m_impl(new SensorSystemImpl()){
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

void SensorSystem::registerb2ContactListener(b2ContactListener* listener) {
	m_impl->registerb2ContactListener(listener);
}
