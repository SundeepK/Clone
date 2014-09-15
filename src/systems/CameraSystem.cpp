#include <systems/CameraSystem.h>

CameraSystem::CameraSystem(int width, int height) : Base(anax::ComponentFilter().requires<PlayerTagComponent, PhysicsComponent>()),
													m_screenWidth(width), m_screenHeight(height), m_view(sf::FloatRect(0,0, m_screenWidth, m_screenHeight)) {

}

CameraSystem::~CameraSystem() {
}

void CameraSystem::update(){
	int halfWidth = m_screenWidth / 2;
	int halfHeight = m_screenHeight / 2;

	auto entity = *getEntities().begin();
	auto& physicsComponent = entity.getComponent<PhysicsComponent>();
	b2Body* body = physicsComponent.physicsBody;
	Vec position(body->GetPosition());
	sf::Vector2f bodyPosInPix = position.mToPix().toSFMLv();

	sf::Vector2f cameraCenterPos(0, 0);

	if (bodyPosInPix.x >= halfWidth) {
		cameraCenterPos.x = bodyPosInPix.x;
	} else {
		cameraCenterPos.x =halfWidth ;
	}

	if (bodyPosInPix.y <= halfHeight) {
		cameraCenterPos.y = bodyPosInPix.y;
	} else {
		cameraCenterPos.y = halfHeight;
	}
	m_view.setCenter(floor(cameraCenterPos.x), cameraCenterPos.y);
}

void CameraSystem::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	rt.setView(m_view);
}
