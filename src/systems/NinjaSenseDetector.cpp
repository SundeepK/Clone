#include <systems/NinjaSenseDetector.h>
#include <Box2D/Box2D.h>
#include <systems/NinjaSenseEntityTagger.h>
#include <components/PlayerTagComponent.h>
#include <tmx/tmx2box2d.h>
#include <SFML/Graphics.hpp>
#include <components/PhysicsComponent.h>

class NinjaSenseDetector::NinjaSenseDetectorImpl{

public:
	std::unique_ptr<b2World> m_b2world;
	NinjaSenseEntityTagger m_ninjaSenseEntityTagger;
	sf::RectangleShape m_ninjaSenseAABB;
	static const int SIZE = 350;

	NinjaSenseDetectorImpl(b2World& b2world) : m_b2world(&b2world) {}
	~NinjaSenseDetectorImpl(){}

	void checkForEntitiesAffectedByNinjaSense(std::vector<anax::Entity>& entities) {

		auto playerEntity = entities[0];
	    auto& physicsComp = playerEntity.getComponent<PhysicsComponent>();
	    b2Body* body = physicsComp.physicsBody;
	    b2Vec2 center = body->GetWorldCenter();

	    int centerPoint = (SIZE/2)/30;
	    sf::Vector2f sfSize(centerPoint,centerPoint);
		sf::Vector2f sfCenter = tmx::BoxToSfVec(b2Vec2(center.x - sfSize.x, center.y - sfSize.y));

		m_ninjaSenseAABB.setPosition(sfCenter.x, sfCenter.y);
		m_ninjaSenseAABB.setSize(sf::Vector2f(SIZE, SIZE));
		m_ninjaSenseAABB.setFillColor(sf::Color(30,30,30));

	    b2AABB aabb;
	    aabb.lowerBound = tmx::SfToBoxVec(sf::Vector2f(m_ninjaSenseAABB.getPosition().x, m_ninjaSenseAABB.getPosition().y + SIZE));
	    aabb.upperBound = tmx::SfToBoxVec(sf::Vector2f(m_ninjaSenseAABB.getPosition().x + SIZE, m_ninjaSenseAABB.getPosition().y));

//	    aabb.lowerBound = b2Vec2(center.x - 5, center.y - 5);
//	    aabb.upperBound = b2Vec2(center.x + 5, center.y + 5);
		m_b2world->QueryAABB(&m_ninjaSenseEntityTagger, aabb);


	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		rt.draw(m_ninjaSenseAABB, states);
	}

};

NinjaSenseDetector::NinjaSenseDetector(b2World& b2world) : Base(anax::ComponentFilter().requires<PlayerTagComponent>()), m_impl(new NinjaSenseDetectorImpl(b2world)) {
}

NinjaSenseDetector::~NinjaSenseDetector(){
}

void NinjaSenseDetector::checkForEntitiesAffectedByNinjaSense() {
	auto entities = getEntities();
	m_impl->checkForEntitiesAffectedByNinjaSense(entities);

}

void NinjaSenseDetector::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

