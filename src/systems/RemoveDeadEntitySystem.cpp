#include <systems/RemoveDeadEntitySystem.h>
#include <vector>
#include <components/PhysicsComponent.h>

class RemoveDeadEntitySystem::RemoveDeadEntitySystemImpl{

public:
	RemoveDeadEntitySystemImpl(b2World& box2dWorld) : m_box2dWorld(&box2dWorld){}
	~RemoveDeadEntitySystemImpl(){}

	std::unique_ptr<b2World> m_box2dWorld;

	void update(std::vector<anax::Entity>& entities){
		for(anax::Entity entity : entities){
			auto& physcisComp = entity.getComponent<PhysicsComponent>();
			if(physcisComp.isDead){
			  m_box2dWorld->DestroyBody(physcisComp.physicsBody);
			  entity.kill();
			}
		}
	}

};

RemoveDeadEntitySystem::RemoveDeadEntitySystem(b2World& box2dWorld) : Base(anax::ComponentFilter().requires<PhysicsComponent>()), m_impl(new RemoveDeadEntitySystemImpl(box2dWorld)){
}

RemoveDeadEntitySystem::~RemoveDeadEntitySystem() {
}

void RemoveDeadEntitySystem::update() {
	auto entities = getEntities();
	m_impl->update(entities);
}
