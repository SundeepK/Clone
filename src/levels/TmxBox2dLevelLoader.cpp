#include "TmxBox2dLevelLoader.h"

TmxBox2dLevelLoader::TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory) : m_mapLoader(&mapDirectory) {
}

TmxBox2dLevelLoader::~TmxBox2dLevelLoader() {
}


std::vector<b2Vec2> parseTexCoordsFromTmxObject(std::string texCoordsToParse){
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


void TmxBox2dLevelLoader::loadSplittableObjects( tmx::MapObjects& mapObject, anax::World& anaxWorld, b2World& b2dworld){
		for ( auto& object : mapObject) {
			auto objectEntity = anaxWorld.createEntity();
		    auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
		    auto& physComp = objectEntity.addComponent<PhysicsComponent>();

	        if (!texCoordsComp.image.loadFromFile("maps/" + object.GetPropertyString("Texture")))
	        		std::cout << "unable to load texture from tmx" << std::endl;
	        texCoordsComp.image.flipVertically();

	        m_textureLoader.loadAsOpenglTexture(texCoordsComp);

	        texCoordsComp.textCoords = parseTexCoordsFromTmxObject(object.GetPropertyString("TexCoords"));
	        physComp.physicsBody = tmx::BodyCreator::Add(object, b2dworld, b2_dynamicBody);
	        objectEntity.activate();
		}
}

void TmxBox2dLevelLoader::loadStaticObjects(const tmx::MapObjects& mapObject, b2World& b2dworld) {
	for ( auto& object : mapObject) {
		tmx::BodyCreator::Add(object, b2dworld);
	}
}

void TmxBox2dLevelLoader::loadTmxLayerForLevel(tmx::MapLayer& layer, b2World& b2dworld, anax::World& anaxWorld){
	if (layer.name == "StaticObjects") {
		loadStaticObjects(layer.objects, b2dworld);
	}
	if (layer.name == "SplittableObjects") {
		loadSplittableObjects(layer.objects, anaxWorld, b2dworld);
	}
}

void TmxBox2dLevelLoader::loadLevel(std::string levelName, b2World& b2dworld, anax::World& anaxWorld) {
	m_mapLoader->Load(levelName);
	auto& layers = m_mapLoader->GetLayers();
	const std::string t = "TexCoords";
	for ( auto& layer : layers) {
		loadTmxLayerForLevel(layer, b2dworld, anaxWorld);
	}
}
