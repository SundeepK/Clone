#include "Box2dLevelLoader.h"

Box2dLevelLoader::Box2dLevelLoader(b2World& b2dworld, tmx::MapLoader& mapLoader) :
		m_b2World(b2dworld), m_mapLoader(&mapLoader) {
}

Box2dLevelLoader::~Box2dLevelLoader() {
}

void Box2dLevelLoader::loadLevel(std::string levelName, b2World& b2dworld) {
	m_mapLoader->Load(levelName);

	const std::vector<tmx::MapLayer>& layers = m_mapLoader->GetLayers();
	for (const auto& l : layers) {
		if (l.name == "Static") {
			for (const auto& object : l.objects) {
				b2Body* b = tmx::BodyCreator::Add(object, m_b2World);
				//sf::Vector2f pos = tmx::BoxToSfVec(b->GetPosition());

			}
		}

	}
}
