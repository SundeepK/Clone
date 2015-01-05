#include <systems/NinjaSenseDetector.h>
#include <Box2D/Box2D.h>
#include <systems/NinjaSenseEntityTagger.h>
#include <components/PlayerTagComponent.h>
#include <tmx/tmx2box2d.h>
#include <SFML/Graphics.hpp>

class NinjaSenseDetector::NinjaSenseDetectorImpl{

	b2World m_b2world;
	NinjaSenseEntityTagger m_ninjaSenseEntityTagger;
	sf::RectangleShape m_ninjaSenseAABB;

	NinjaSenseDetectorImpl(b2World& b2world) : m_b2world(b2world) {}
	~NinjaSenseDetectorImpl(){}

	void checkForEntitiesAffectedByNinjaSense(std::vector<anax::Entity>& entities) {
		auto playerEntity = entities[0];
	    auto& physicsComp = playerEntity.getComponent<PhysicsComponent>();
	    b2Body* body = physicsComp.physicsBody;
	    b2Vec2 center = body->GetWorldCenter();

	    b2AABB aabb;
	    aabb.lowerBound = b2Vec2(center.x - 5, center.y - 5);
	    aabb.upperBound = b2Vec2(center.x + 5, center.y + 5);
		m_b2world.QueryAABB(&m_ninjaSenseEntityTagger, aabb);

		sf::Vector2 sfCenter = tmx::BoxToSfVec(b2Vec2(center.x - 5, center.y + 5));
		m_ninjaSenseAABB.setPosition(sfCenter.x, sfCenter.y);

	}

};

NinjaSenseDetector::NinjaSenseDetector(b2World& b2world) : m_impl(new NinjaSenseDetector(b2world)) {
}

NinjaSenseDetector::~NinjaSenseDetector() : Base(anax::ComponentFilter().requires<PlayerTagComponent>()) {
}

void NinjaSenseDetector::checkForEntitiesAffectedByNinjaSense() {
	auto entities = getEntities();
	m_impl->checkForEntitiesAffectedByNinjaSense();

}
