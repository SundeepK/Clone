#include <systems/DrawStaticAABBSystem.h>
#include <components/PhysicsComponent.h>
#include <components/AABBComponent.h>

class DrawStaticAABBSystem::DrawStaticAABBSystemImpl{

public:

	std::vector<sf::RectangleShape> m_aabbsToDraw;

	DrawStaticAABBSystemImpl(){
	}

	~DrawStaticAABBSystemImpl(){
	}

	void updateAABBs(std::vector<anax::Entity>& entities) {
		m_aabbsToDraw.clear();
		for(auto entity : entities){
			auto aabbComp = entity.getComponent<AABBComponent>();
			sf::RectangleShape rect;
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineThickness(2.f);
			rect.setOutlineColor(aabbComp.getColor());
			rect.setPosition(sf::Vector2f(aabbComp.aabb.left, aabbComp.aabb.top));
			rect.setSize(sf::Vector2f(aabbComp.aabb.width, aabbComp.aabb.height));
			m_aabbsToDraw.push_back(rect);
		}

	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		for(auto aabb : m_aabbsToDraw){
			rt.draw(aabb);
		}
	}

};


DrawStaticAABBSystem::DrawStaticAABBSystem() : Base(anax::ComponentFilter().requires<PhysicsComponent,AABBComponent>()), m_impl(new DrawStaticAABBSystemImpl()) {

}

DrawStaticAABBSystem::~DrawStaticAABBSystem() {
}

void DrawStaticAABBSystem::updateAABBs() {
	auto entities = getEntities();
	m_impl->updateAABBs(entities);
}

void DrawStaticAABBSystem::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}
