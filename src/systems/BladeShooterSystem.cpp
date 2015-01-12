#include <systems/BladeShooterSystem.h>
#include <vector>
#include <components/PhysicsComponent.h>
#include <components/BladeShooterComponent.h>

class BladeShooterSystem::BladeShooterSystemImpl{

	BladeShooterSystemImpl(){}
	~BladeShooterSystemImpl(){}

	void update(std::vector<anax::Entity>& entities){

	}

};

BladeShooterSystem::BladeShooterSystem() : Base(anax::ComponentFilter().requires<PhysicsComponent,BladeShooterComponent>()) {
}

BladeShooterSystem::~BladeShooterSystem() {
}

void BladeShooterSystem::update(){
	auto entities = getEntities();
	m_impl->update(entities);
}



