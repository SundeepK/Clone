#include "TmxBox2dLevelLoader.h"

TmxBox2dLevelLoader::TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory) : m_mapLoader(&mapDirectory) {
}

TmxBox2dLevelLoader::~TmxBox2dLevelLoader() {
}


std::vector<b2Vec2> parseTexCoordsFromMapObject(std::string texCoordsToParse){
	 std::stringstream texCoordStream(texCoordsToParse);
	 std::vector<b2Vec2> textureCoords;
	 int count = 0;
	 std::string texCoord;
	 float x;
	 while(std::getline(texCoordStream,texCoord,',')){
		 count++;

		 float value = std::stof(texCoord);
		 if(count % 2 == 0){
			 textureCoords.push_back(b2Vec2(x, value));
		 }else{
			x = value;
		 }
	 }
	 return textureCoords;
}

void TmxBox2dLevelLoader::loadLevel(std::string levelName, b2World& b2dworld, anax::World& anaxWorld) {
	m_mapLoader->Load(levelName);
	 std::vector<tmx::MapLayer>& layers = m_mapLoader->GetLayers();
	const std::string t = "TexCoords";
	for ( auto& l : layers) {
		if (l.name == "StaticObjects") {
			for ( auto& object : l.objects) {
				tmx::BodyCreator::Add(object, b2dworld);
			}
		}

		if (l.name == "SplittableObjects") {
			for ( auto& object : l.objects) {
				std::vector<b2Vec2> texs =  parseTexCoordsFromMapObject(object.GetPropertyString(t));
				for ( auto& texcoord : texs) {
					std::cout << "x: " << texcoord.x << "  y: " << texcoord.y << std::endl;
				}
			}
		}

	}
}
