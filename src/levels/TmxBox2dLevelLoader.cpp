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
				auto objectEntity = anaxWorld.createEntity();
			    auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
			    auto& physComp = objectEntity.addComponent<PhysicsComponent>();

		        if (!texCoordsComp.image.loadFromFile("maps/" + object.GetPropertyString("Texture")))
		        		std::cout << "unable to load texture from tmx" << std::endl;
		        texCoordsComp.image.flipVertically();

		        texCoordsComp.textCoords = parseTexCoordsFromMapObject(object.GetPropertyString(t));
		        physComp.physicsBody = tmx::BodyCreator::Add(object, b2dworld, b2_dynamicBody);
//		        physComp.physicsBody->GetFixtureList()->SetDensity(1.0f);
//		        physComp.physicsBody->ResetMassData();
		        objectEntity.activate();
			}
		}

	}
}
