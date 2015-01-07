#include <systems/NinjaSenseDetector.h>
#include <Box2D/Box2D.h>
#include <systems/NinjaSenseEntityTagger.h>
#include <components/PlayerTagComponent.h>
#include <tmx/tmx2box2d.h>
#include <SFML/Graphics.hpp>
#include <components/PhysicsComponent.h>
#include <components/NinjaSenseComponent.h>

class NinjaSenseDetector::NinjaSenseDetectorImpl{

public:
	std::unique_ptr<b2World> m_b2world;
	NinjaSenseEntityTagger m_ninjaSenseEntityTagger;
	sf::RectangleShape m_ninjaSenseAABB;
	static const int SIZE = 350;

	NinjaSenseDetectorImpl(b2World& b2world) : m_b2world(&b2world) {}
	~NinjaSenseDetectorImpl(){}

	void checkForEntitiesAffectedByNinjaSense(std::vector<anax::Entity>& entities) {
		//we only have one entity here which is the player
		auto playerEntity = entities[0];
	    auto& physicsComp = playerEntity.getComponent<PhysicsComponent>();
	    auto& ninjaSense =  playerEntity.getComponent<NinjaSenseComponent>();

	    b2AABB aabb = ninjaSense.ninjaSenseFixture->GetAABB(0);

		sf::Vector2f drawableNinjaSensePos = tmx::BoxToSfVec(b2Vec2(aabb.lowerBound.x, aabb.lowerBound.y ));

		m_ninjaSenseAABB.setPosition(drawableNinjaSensePos.x, drawableNinjaSensePos.y);
		m_ninjaSenseAABB.setSize(tmx::BoxToSfVec(b2Vec2(ninjaSense.ninjaSenseRectSize.x * 2, ninjaSense.ninjaSenseRectSize.y *2)));
		m_ninjaSenseAABB.setFillColor(sf::Color(30,30,30));

		m_b2world->QueryAABB(&m_ninjaSenseEntityTagger, aabb);

	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		rt.draw(m_ninjaSenseAABB, states);
	}

};

NinjaSenseDetector::NinjaSenseDetector(b2World& b2world) : Base(anax::ComponentFilter().requires<PlayerTagComponent, NinjaSenseComponent>()), m_impl(new NinjaSenseDetectorImpl(b2world)) {
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

