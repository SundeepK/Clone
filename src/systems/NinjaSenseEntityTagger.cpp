#include <systems/NinjaSenseEntityTagger.h>
#include <vector>
#include <components/NinjaSenseComponent.h>
#include <components/Texcoords.h>
#include <components/SplitDirectionComponent.h>
#include <components/PhysicsComponent.h>

class NinjaSenseEntityTagger::NinjaSenseEntityTaggerImpl{

public:
	NinjaSenseEntityTaggerImpl(){
	}

	~NinjaSenseEntityTaggerImpl() {
	}

	bool ReportFixture(b2Fixture* fixture, std::vector<anax::Entity> entities) {
		for(auto entity : entities){
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			b2Body* body = physicsComponent.physicsBody;
			//we always assume body only has one fixture
			//TODO do we need to iterate all body fixture?
			if(fixture == body->GetFixtureList()){
			 	entity.addComponent<NinjaSenseComponent>();
			}
		}
		return true;
	}


};


NinjaSenseEntityTagger::NinjaSenseEntityTagger() : Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent, SplitDirectionComponent>()), 	m_impl(new NinjaSenseEntityTaggerImpl()) {
}

NinjaSenseEntityTagger::~NinjaSenseEntityTagger() {
}

bool NinjaSenseEntityTagger::ReportFixture(b2Fixture* fixture) {
	auto entities = getEntities();
	return	m_impl->ReportFixture(fixture, entities);
}
