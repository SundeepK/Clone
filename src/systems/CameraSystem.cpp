#include <systems/CameraSystem.h>

class CameraSystem::CameraSystemImpl {

public:
	CameraSystemImpl(int width, int height) : m_screenWidth(width), m_screenHeight(height), m_view(sf::FloatRect(0,0, m_screenWidth, m_screenHeight)) {
	}

public:
	sf::Vector2f getCameraPosition(std::vector<anax::Entity>& entities);

	int m_screenWidth;
	int m_screenHeight;
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
	sf::View m_view;
};

sf::Vector2f CameraSystem::CameraSystemImpl::getCameraPosition(std::vector<anax::Entity>& entities) {
	int halfWidth = m_screenWidth / 2;
	int halfHeight = m_screenHeight / 2;
	sf::Vector2f cameraCenterPos(halfWidth, halfHeight);

	if(entities.size() > 0){
	auto entity = *entities.begin();
	auto& physicsComponent = entity.getComponent<PhysicsComponent>();
	b2Body* body = physicsComponent.physicsBody;
	Vec position(body->GetPosition());
	sf::Vector2f bodyPosInPix = position.mToPix().toSFMLv();


	if (bodyPosInPix.x >= halfWidth) {
		cameraCenterPos.x = bodyPosInPix.x;
	}

	if (bodyPosInPix.y <= halfHeight) {
		cameraCenterPos.y = bodyPosInPix.y;
	}
		return cameraCenterPos;
	}else{
		return sf::Vector2f();
	}
}


CameraSystem::CameraSystem(int width, int height) : Base(anax::ComponentFilter().requires<PlayerTagComponent, PhysicsComponent>()), m_impl(new CameraSystemImpl(width, height)) {
}

CameraSystem::~CameraSystem() {
}


void CameraSystem::update(){
	auto entities = getEntities();
	sf::Vector2f cameraPos = m_impl->getCameraPosition(entities);
	m_impl->m_view.setCenter(floor(cameraPos.x), cameraPos.y);
}

void CameraSystem::updateOpenglCamera() {
	auto entities = getEntities();
	sf::Vector2f cameraPos = m_impl->getCameraPosition(entities);
    glTranslatef( -cameraPos.x + m_impl->m_screenWidth/2, -cameraPos.y + m_impl->m_screenHeight/2, 0);
}

sf::View CameraSystem::getView() {
	return m_impl->m_view;
}

void CameraSystem::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	rt.setView(m_impl->m_view);
}


sf::Vector2f CameraSystem::getCamerPos() {
	auto entities = getEntities();
	return m_impl->getCameraPosition(entities);
}
