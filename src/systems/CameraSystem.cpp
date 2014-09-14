#include <systems/CameraSystem.h>

CameraSystem::CameraSystem() : Base(anax::ComponentFilter().requires<PlayerStateComponent, PhysicsComponent>()), m_view(sf::FloatRect(0,0, 1280, 800)) {

}

CameraSystem::~CameraSystem() {
}

void CameraSystem::update(){
    auto entities = getEntities();
    for(auto entity : entities){
    		auto& physicsComponent = entity.getComponent<PhysicsComponent>();
    		b2Body* body = physicsComponent.physicsBody;
    		b2Vec2 position = body->GetPosition();

    		sf::Vector2f cameraCenterPos(0,0);

    		if((position.x * 30.0f) >= (1280 / 2)){
    			cameraCenterPos.x = position.x  * 30.0f;
    		}else{
    			cameraCenterPos.x = (1280 / 2);
    		}

    		if((position.y * 30.0f) <= (800 / 2)){
    			cameraCenterPos.y = position.y  * 30.0f;
    		}else{
    			cameraCenterPos.y = 800 /2;
    		}
    		m_view.setCenter(floor(cameraCenterPos.x), cameraCenterPos.y);
    }
}

void CameraSystem::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	rt.setView(m_view);
}
