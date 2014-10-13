#include <systems/CameraSystem.h>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>
#include <Vec.h>
#include <components/PhysicsComponent.h>
#include <components/PlayerTagComponent.h>

class CameraSystem::CameraSystemImpl {

public:
	CameraSystemImpl(int width, int height) : m_screenWidth(width), m_screenHeight(height), m_view(sf::FloatRect(0,0, m_screenWidth, m_screenHeight)),
											m_cameraCenterPos(m_screenWidth/2, m_screenHeight/2) {
	}

public:
	sf::Vector2f getCameraPosition(std::vector<anax::Entity>& entities);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	int m_screenWidth;
	int m_screenHeight;
	sf::View m_view;
	sf::Vector2f m_cameraCenterPos;

};

sf::Vector2f CameraSystem::CameraSystemImpl::getCameraPosition(std::vector<anax::Entity>& entities) {
	sf::Vector2f cameraPositon = m_cameraCenterPos;

	if(entities.size() > 0){
	auto entity = *entities.begin();
	auto& physicsComponent = entity.getComponent<PhysicsComponent>();
	b2Body* body = physicsComponent.physicsBody;
	Vec position(body->GetPosition());
	sf::Vector2f bodyPosInPix = position.mToPix().toSFMLv();


	if (bodyPosInPix.x >= m_cameraCenterPos.x) {
		cameraPositon.x = floor(bodyPosInPix.x);
	}

	if (bodyPosInPix.y <= m_cameraCenterPos.y) {
		cameraPositon.y = floor(bodyPosInPix.y);
	}
	}else{
		cameraPositon = sf::Vector2f();
	}

	return cameraPositon;
}


CameraSystem::CameraSystem(int width, int height) : Base(anax::ComponentFilter().requires<PlayerTagComponent, PhysicsComponent>()), m_impl(new CameraSystemImpl(width, height)) {
}

CameraSystem::~CameraSystem() {
}


void CameraSystem::update(){
	auto entities = getEntities();
	sf::Vector2f cameraPos = m_impl->getCameraPosition(entities);
	m_impl->m_view.setCenter(cameraPos.x, cameraPos.y);
}

void CameraSystem::updateOpenglCamera() {
	auto entities = getEntities();
	sf::Vector2f cameraPos = m_impl->getCameraPosition(entities);
    glTranslatef( -cameraPos.x + m_impl->m_cameraCenterPos.x, -cameraPos.y + m_impl->m_cameraCenterPos.y, 0);
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
