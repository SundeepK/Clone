#include <systems/TextureRectRenderSystem.h>

class TextureRectRenderSystem::TextureRectRenderSystemImpl{
public:
	TextureRectRenderSystemImpl(){
	}

	~TextureRectRenderSystemImpl() {
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states, std::vector<anax::Entity>& entities) const{
	    for(auto& entity : entities)
	    {
	      //  auto& textureRect = entity.getComponent<TextureRectComponent>().rect;
			auto& physicsComp = entity.getComponent<PhysicsComponent>();
	        auto physicsb2Body = entity.getComponent<PhysicsComponent>().physicsBody;
			b2Vec2 center = physicsComp.smoothedPosition;

	       // textureRect.setPosition(sf::Vector2f(floor(physicsb2Body->GetPosition().x*30-10),floor(physicsb2Body->GetPosition().y*30-10)));

	        auto& animationComp = entity.getComponent<AnimationComponent>().m_sprite;
	        animationComp.setPosition(sf::Vector2f(floor(center.x*30),floor(center.y*30)));
	        rt.draw(animationComp);
	    }
	}

};

TextureRectRenderSystem::TextureRectRenderSystem() : Base(anax::ComponentFilter().requires<AnimationComponent, PhysicsComponent>()), m_impl(new TextureRectRenderSystemImpl()) {
}

TextureRectRenderSystem::~TextureRectRenderSystem() {
}

void TextureRectRenderSystem::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	auto entities = getEntities();
	m_impl->draw(rt, states, entities);
}
