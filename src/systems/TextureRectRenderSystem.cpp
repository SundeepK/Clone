#include <systems/TextureRectRenderSystem.h>

TextureRectRenderSystem::TextureRectRenderSystem() : Base(anax::ComponentFilter().requires<AnimationComponent, PhysicsComponent>()) {
}

TextureRectRenderSystem::~TextureRectRenderSystem() {
}

void TextureRectRenderSystem::render(sf::RenderTarget* renderTarget) {
    auto entities = getEntities();
    for(auto& entity : entities)
    {
      //  auto& textureRect = entity.getComponent<TextureRectComponent>().rect;
		auto& physicsComp = entity.getComponent<PhysicsComponent>();
        auto physicsb2Body = entity.getComponent<PhysicsComponent>().physicsBody;
		b2Vec2 center = physicsComp.smoothedPosition;

       // textureRect.setPosition(sf::Vector2f(floor(physicsb2Body->GetPosition().x*30-10),floor(physicsb2Body->GetPosition().y*30-10)));

        auto& animationComp = entity.getComponent<AnimationComponent>().m_sprite;
        animationComp.setPosition(sf::Vector2f(floor(center.x*30-10),floor(center.y*30-10)));
        renderTarget->draw(animationComp);
    }

}
