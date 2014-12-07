#include "TmxBox2dLevelLoader.h"

extern "C"
{
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/object.hpp>
#include <components/PhysicsComponent.h>

class TmxBox2dLevelLoader::TmxBox2dLevelLoaderImpl{
public:

	std::unique_ptr<tmx::MapLoader> m_mapLoader;
	std::unique_ptr<b2World> m_box2dWorld;
	std::unique_ptr<anax::World> m_anaxWorld;
	std::unordered_map<std::string, SplitDirection> m_splitDirectionMap;
	std::vector<std::string> m_levelsToLoad;
	WorldEntityLoader m_worldEntityLoader;
	int m_currentLevelIndex = 0;

	TmxBox2dLevelLoaderImpl(tmx::MapLoader& mapDirectory, b2World& b2dworld, anax::World& anaxWorld) : m_mapLoader(&mapDirectory), m_box2dWorld(&b2dworld), m_anaxWorld(&anaxWorld) {
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

	std::unordered_map<std::string, tmx::MapObject> loadSplittableObjects( tmx::MapObjects& mapObject, anax::World& anaxWorld, b2World& b2dworld){
		std::unordered_map<std::string, tmx::MapObject> mapObjects;
		for (auto& object : mapObject) {

			if (!object.GetName().empty()) {
				mapObjects.insert(std::pair<std::string, tmx::MapObject>(object.GetName(), object));
			}

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

			if (object.GetPropertyString("Body") == "dynamic") {
				physComp.physicsBody = tmx::BodyCreator::Add(object, b2dworld, b2_dynamicBody);
			} else {
				physComp.physicsBody = tmx::BodyCreator::Add(object, b2dworld, b2_staticBody);
			}

			splitDirectionComp.splitDirection = parseSplitDirection(object.GetPropertyString("SplitDir"));

			objectEntity.activate();
		}
		return mapObjects;
	}

	std::unordered_map<std::string, tmx::MapObject> loadStaticObjects(const tmx::MapObjects& mapObject, b2World& b2dworld) {
		std::unordered_map<std::string, tmx::MapObject> mapObjects;
		for (auto& object : mapObject) {
			if (!object.GetName().empty()) {
				mapObjects.insert(std::pair<std::string, tmx::MapObject>(object.GetName(), object));
			}
			tmx::BodyCreator::Add(object, b2dworld);
		}
		return mapObjects;
	}

	std::unordered_map<std::string, tmx::MapObject> loadMiscMapObjects(const tmx::MapObjects& mapObject) {
		std::unordered_map<std::string, tmx::MapObject> mapObjects;
		for (auto& object : mapObject) {
			if (!object.GetName().empty()) {
				mapObjects.insert(std::pair<std::string, tmx::MapObject>(object.GetName(), object));
			}
		}
		return mapObjects;
	}


	std::unordered_map<std::string, tmx::MapObject> loadTmxLayerForLevel(tmx::MapLayer& layer, b2World& b2dworld, anax::World& anaxWorld){
		std::unordered_map<std::string, tmx::MapObject> mapObjects;
		if (layer.name == "StaticObjects") {
			auto objectsMap =  loadStaticObjects(layer.objects, b2dworld);
			mapObjects.insert(objectsMap.begin(), objectsMap.end());
		}else if (layer.name == "SplittableObjects") {
			auto objectsMap =  loadSplittableObjects(layer.objects, anaxWorld, b2dworld);
			mapObjects.insert(objectsMap.begin(), objectsMap.end());
		}else{
			auto objectsMap =  loadMiscMapObjects(layer.objects);
			mapObjects.insert(objectsMap.begin(), objectsMap.end());
		}
		return mapObjects;
	}

	void loadLevelList(lua_State *luaState){
		if(luaL_dofile(luaState, "lua-scripts/levelsConfig.lua")){
	        printf("%s\n", lua_tostring(luaState, -1));
		}

		try {
			luabind::object levels =  luabind::call_function<luabind::object>(luaState, "getLevelsToLoad");
			for(int i = 1; ; i++){
				if(levels[i]){
				  std::string levelName =  luabind::object_cast<std::string>(levels[i]);
				    std::cout << "level is" << levelName << std::endl;
				  m_levelsToLoad.push_back(levelName);
				}else{
					break;
				}
			}
		} catch (luabind::error& e) {
		    std::string error = lua_tostring(e.state(), -1);
		    std::cout << error << std::endl;
		}

		assert(m_levelsToLoad.size() > 1 && "No level names found");
	}

	void loadNextLevel() {
	    lua_State *luaState = luaL_newstate();
	    luabind::open(luaState);
		luaL_openlibs(luaState);

		if(m_levelsToLoad.size() <= 0 && m_currentLevelIndex <= 0){
			loadLevelList(luaState);
		}

		if(m_currentLevelIndex < m_levelsToLoad.size()){
			auto entities = m_anaxWorld->getEntities();
			for(anax::Entity entity : entities){
				if(entity.hasComponent<PhysicsComponent>()){
					auto& physicsComp = entity.getComponent<PhysicsComponent>();
					m_box2dWorld->DestroyBody(physicsComp.physicsBody);
				}
			}

			m_anaxWorld->killEntities(entities);
			m_mapLoader->Load(m_levelsToLoad[m_currentLevelIndex]);
			m_currentLevelIndex++;
			std::vector<tmx::MapLayer>& layers = m_mapLoader->GetLayers();
			std::unordered_map<std::string, tmx::MapObject> loadedItems;
			const std::string t = "TexCoords";
			for (auto& layer : layers) {
				if (layer.visible) {
					auto objectsMap = loadTmxLayerForLevel(layer, *m_box2dWorld, *m_anaxWorld);
					loadedItems.insert(objectsMap.begin(), objectsMap.end());
				}
			}

			m_worldEntityLoader.loadWorldEntities(*m_anaxWorld, *m_box2dWorld, loadedItems, luaState);
		}
		lua_close(luaState);
	}

};

TmxBox2dLevelLoader::TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory, b2World& b2dworld, anax::World& anaxWorld) : Base(anax::ComponentFilter()),
		m_impl(new TmxBox2dLevelLoaderImpl(mapDirectory, b2dworld, anaxWorld)) {
}

TmxBox2dLevelLoader::~TmxBox2dLevelLoader() {
}

void TmxBox2dLevelLoader::loadNextLevel() {
	auto entities = getEntities();
	m_impl->loadNextLevel();
}
