#include "TmxBox2dLevelLoader.h"

extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/object.hpp>
#include <components/PhysicsComponent.h>
#include <levels/Level1.h>
#include <game-objects/Rope.h>
#include <game-objects/GameEntityCreator.h>

class TmxBox2dLevelLoader::TmxBox2dLevelLoaderImpl{
public:

	std::unique_ptr<tmx::MapLoader> m_mapLoader;
	std::unique_ptr<b2World> m_box2dWorld;
	std::unique_ptr<anax::World> m_anaxWorld;
	std::unordered_map<std::string, SplitDirection> m_splitDirectionMap;
	std::vector<LevelObject> m_levelsToLoad;
	WorldEntityLoader m_worldEntityLoader;
	std::unordered_map<std::string, tmx::MapObject> m_levelObjects;
	int m_currentLevelIndex = 0;
	Level1 level1;
	std::unordered_map<std::string, std::unique_ptr<GameEntityCreator>> m_entityCreators;

	TmxBox2dLevelLoaderImpl(tmx::MapLoader& mapDirectory, b2World& b2dworld, anax::World& anaxWorld) : m_mapLoader(&mapDirectory),
			m_box2dWorld(&b2dworld), m_anaxWorld(&anaxWorld), level1(b2dworld, anaxWorld) {
		m_splitDirectionMap["right"] = SplitDirection::RIGHT;
		m_splitDirectionMap["left"] = SplitDirection::LEFT;
		m_splitDirectionMap["top"] =  SplitDirection::TOP;
		m_splitDirectionMap["down"] = SplitDirection::DOWN;

		m_entityCreators["RopeBox"] = std::unique_ptr<GameEntityCreator>(new Rope());
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


	void loadEntities(const tmx::MapObjects& mapObject){
		for (auto& object : mapObject) {
			std::string entityName = object.GetName();
			if ( m_entityCreators.find(entityName) != m_entityCreators.end() ) {
				m_entityCreators[entityName]->createEntity(object, *m_box2dWorld, *m_anaxWorld);
			}else{
				std::cout << "No entity creator found for name: " << entityName << std::endl;
			}
		}
	}


	std::unordered_map<std::string, tmx::MapObject> loadTmxLayerForLevel(tmx::MapLayer& layer, b2World& b2dworld, anax::World& anaxWorld){
		std::unordered_map<std::string, tmx::MapObject> mapObjects;
		if (layer.name == "StaticObjects") {
			auto objectsMap =  loadStaticObjects(layer.objects, b2dworld);
			mapObjects.insert(objectsMap.begin(), objectsMap.end());
		}else if (layer.name == "SplittableObjects") {
			auto objectsMap =  loadSplittableObjects(layer.objects, anaxWorld, b2dworld);
			mapObjects.insert(objectsMap.begin(), objectsMap.end());
		}else if(layer.name == "Entities"){
			loadEntities(layer.objects);
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
					LevelObject levelName =  luabind::object_cast<LevelObject>(levels[i]);
				    std::cout << "level is" << levelName.levelMapName<< std::endl;
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

		luabind::module(luaState)[
		luabind::class_<LevelObject>("LevelObject")
		      .def(luabind::constructor<>())
		      .def_readwrite("levelMapName", &LevelObject::levelMapName)
		      .def_readwrite("scriptName", &LevelObject::scriptName)
		];

		if(m_levelsToLoad.size() <= 0 && m_currentLevelIndex <= 0){
			loadLevelList(luaState);
		}

		if(m_currentLevelIndex < m_levelsToLoad.size()){
			auto entities = m_anaxWorld->getEntities();
			for(anax::Entity entity : entities){
				if(entity.hasComponent<PhysicsComponent>()){
					auto& physicsComp = entity.getComponent<PhysicsComponent>();
					delete(physicsComp.physicsBody->GetUserData());
					m_box2dWorld->DestroyBody(physicsComp.physicsBody);
				}
			}

			m_anaxWorld->killEntities(entities);
			m_mapLoader->Load(m_levelsToLoad[m_currentLevelIndex].levelMapName);
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
			m_levelObjects = loadedItems;
			m_worldEntityLoader.loadWorldEntities(*m_anaxWorld, *m_box2dWorld, loadedItems, luaState);
		}
		lua_close(luaState);
		level1.loadLevel(m_levelObjects);
	}

	void update() {
		level1.updateLevel();
	}

	void BeginContact(b2Contact* contact) {
		level1.BeginContact(contact);

	}

	void EndContact(b2Contact* contact) {
		level1.EndContact(contact);

	}

	sf::Vector2u getMapSize(){
		return m_mapLoader->GetMapSize();
	}



};

TmxBox2dLevelLoader::TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory, b2World& b2dworld, anax::World& anaxWorld, SensorSystem& sensor) : Base(anax::ComponentFilter()),
		m_impl(new TmxBox2dLevelLoaderImpl(mapDirectory, b2dworld, anaxWorld)) {
}

TmxBox2dLevelLoader::~TmxBox2dLevelLoader() {
}

void TmxBox2dLevelLoader::loadNextLevel() {
	auto entities = getEntities();
	m_impl->loadNextLevel();
}

void TmxBox2dLevelLoader::update() {
	m_impl->update();
}

void TmxBox2dLevelLoader::BeginContact(b2Contact* contact) {
	m_impl->BeginContact(contact);

}

void TmxBox2dLevelLoader::EndContact(b2Contact* contact) {
	m_impl->EndContact(contact);

}

sf::Vector2u TmxBox2dLevelLoader::getMapSize() {
	return m_impl->getMapSize();
}
