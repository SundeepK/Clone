#include "TmxBox2dLevelLoader.h"

class TmxBox2dLevelLoader::TmxBox2dLevelLoaderImpl{
public:

	std::unique_ptr<tmx::MapLoader> m_mapLoader;
	std::unordered_map<std::string, SplitDirection> m_splitDirectionMap;

	TmxBox2dLevelLoaderImpl(tmx::MapLoader& mapDirectory) : m_mapLoader(&mapDirectory) {
		m_splitDirectionMap["right"] = SplitDirection::RIGHT;
		m_splitDirectionMap["left"] = SplitDirection::LEFT;
		m_splitDirectionMap["top"] =  SplitDirection::TOP;
		m_splitDirectionMap["down"] = SplitDirection::DOWN;
	}

	~TmxBox2dLevelLoaderImpl() {}

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


	SplitDirection parseSplitDirection(std::string direction){
		auto splitDirection =  m_splitDirectionMap.find(direction);
		std::cout << "dir: " << direction << std::endl;
    	assert (
    		"Split direction is not found" &&
    		splitDirection != m_splitDirectionMap.end()
    	);
    	return splitDirection->second;
	}

	void loadSplittableObjects( tmx::MapObjects& mapObject, anax::World& anaxWorld, b2World& b2dworld){
			for ( auto& object : mapObject) {
				auto objectEntity = anaxWorld.createEntity();
			    auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
			    auto& physComp = objectEntity.addComponent<PhysicsComponent>();
			    auto& splitDirectionComp = objectEntity.addComponent<SplitDirectionComponent>();

		        if (!texCoordsComp.image.loadFromFile("maps/" + object.GetPropertyString("Texture")))
		        		std::cout << "unable to load texture from tmx" << std::endl;
		        texCoordsComp.image.flipVertically();
		        texCoordsComp.textCoords = parseTexCoordsFromTmxObject(object.GetPropertyString("TexCoords"));

		        texCoordsComp.texture = TextureLoader::loadAsOpenglTexture(texCoordsComp.texture, texCoordsComp.image);
		        std::cout << object.PolyPoints().size() << "points size" << std::endl;

		        if(object.GetPropertyString("Body") == "dynamic"){
			        physComp.physicsBody = tmx::BodyCreator::Add(object, b2dworld, b2_dynamicBody);
		        }else{
			        physComp.physicsBody = tmx::BodyCreator::Add(object, b2dworld, b2_staticBody);
		        }

		        splitDirectionComp.splitDirection = parseSplitDirection(object.GetPropertyString("SplitDir"));

		        objectEntity.activate();
			}
	}

	void loadStaticObjects(const tmx::MapObjects& mapObject, b2World& b2dworld) {
		for ( auto& object : mapObject) {
			tmx::BodyCreator::Add(object, b2dworld);
		}
	}

	void loadTmxLayerForLevel(tmx::MapLayer& layer, b2World& b2dworld, anax::World& anaxWorld){
		if (layer.name == "StaticObjects") {
			loadStaticObjects(layer.objects, b2dworld);
		}
		if (layer.name == "SplittableObjects") {
			loadSplittableObjects(layer.objects, anaxWorld, b2dworld);
		}
	}

	void loadLevel(std::string levelName, b2World& b2dworld, anax::World& anaxWorld) {
		m_mapLoader->Load(levelName);
		 std::vector<tmx::MapLayer>& layers = m_mapLoader->GetLayers();
		const std::string t = "TexCoords";
		for ( auto& layer : layers) {
			if(layer.visible){
			   loadTmxLayerForLevel(layer, b2dworld, anaxWorld);
			}
		}
	}

};

TmxBox2dLevelLoader::TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory) : m_impl(new TmxBox2dLevelLoaderImpl(mapDirectory)) {
}

TmxBox2dLevelLoader::~TmxBox2dLevelLoader() {
}

void TmxBox2dLevelLoader::loadLevel(std::string levelName, b2World& b2dworld,anax::World& anaxWorld) {
	m_impl->loadLevel(levelName, b2dworld, anaxWorld);
}
