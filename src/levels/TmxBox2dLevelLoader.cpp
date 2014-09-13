#include "TmxBox2dLevelLoader.h"

TmxBox2dLevelLoader::TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory) : m_mapLoader(&mapDirectory) {
}

TmxBox2dLevelLoader::~TmxBox2dLevelLoader() {
}

void TmxBox2dLevelLoader::loadLevel(std::string levelName, b2World& b2dworld) {
	m_mapLoader->Load(levelName);
	const std::vector<tmx::MapLayer>& layers = m_mapLoader->GetLayers();
	for (const auto& l : layers) {
		if (l.name == "Static") {
			for (const auto& object : l.objects) {
				tmx::BodyCreator::Add(object, b2dworld);
			}
		}
	}
}
