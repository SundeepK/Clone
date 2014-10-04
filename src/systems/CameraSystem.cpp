#include <systems/CameraSystem.h>

CameraSystem::CameraSystem(int width, int height) : Base(anax::ComponentFilter().requires<PlayerTagComponent, PhysicsComponent>()),
													m_screenWidth(width), m_screenHeight(height), m_view(sf::FloatRect(0,0, m_screenWidth, m_screenHeight)) {

}

CameraSystem::~CameraSystem() {
}

sf::Vector2f CameraSystem::getCameraPosition(){
	int halfWidth = m_screenWidth / 2;
	int halfHeight = m_screenHeight / 2;

	auto entity = *getEntities().begin();
	auto& physicsComponent = entity.getComponent<PhysicsComponent>();
	b2Body* body = physicsComponent.physicsBody;
	Vec position(body->GetPosition());
	sf::Vector2f bodyPosInPix = position.mToPix().toSFMLv();

	sf::Vector2f cameraCenterPos(halfWidth, halfHeight);

	if (bodyPosInPix.x >= halfWidth) {
		cameraCenterPos.x = bodyPosInPix.x;
	}

	if (bodyPosInPix.y <= halfHeight) {
		cameraCenterPos.y = bodyPosInPix.y;
	}
	return cameraCenterPos;
}

void CameraSystem::update(){
	sf::Vector2f cameraPos = getCameraPosition();
	m_view.setCenter(floor(cameraPos.x), cameraPos.y);
}

void CameraSystem::updateOpenglCamera() {
	sf::Vector2f cameraPos = getCameraPosition();
    glTranslatef( -cameraPos.x + m_screenWidth/2, -cameraPos.y + m_screenHeight/2, 0);
}

void CameraSystem::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	rt.setView(m_view);
}
