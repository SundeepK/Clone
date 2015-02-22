#include "TmxBox2dLevelLoader.h"

extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/object.hpp>
#include <levels/Level1.h>
#include <game-objects/RopeBox.h>
#include <game-objects/GameEntityCreator.h>
#include <game-objects/Rope.h>
#include <game-objects/Boulder.h>
#include <game-objects/GameObjectTag.h>
#include <game-objects/BladeShooter.h>
#include <game-objects/DeathFloor.h>
#include <game-objects/DynamicRotatingBlade.h>
#include <game-objects/PlayerEndPoint.h>
#include <game-objects/StaticObject.h>
#include <game-objects/SplittableObject.h>
#include <entity-loaders/PlayerEntityLoader.h>

class TmxBox2dLevelLoader::TmxBox2dLevelLoaderImpl{
public:

	std::unique_ptr<tmx::MapLoader> m_mapLoader;
	std::unique_ptr<b2World> m_box2dWorld;
	std::unique_ptr<anax::World> m_anaxWorld;
	std::vector<LevelObject> m_levelsToLoad;
	unsigned int m_currentLevelIndex = 0;
	std::unique_ptr<LuaScriptLevel> luaScriptLevel;
	std::unordered_map<std::string, std::unique_ptr<GameEntityCreator>> m_entityCreators;
	PlayerEntityLoader m_playerEntityLoader;
	StaticObject m_staticObjectCreator;
	SplittableObject m_splittableObjectCreator;

	TmxBox2dLevelLoaderImpl(tmx::MapLoader& mapDirectory, b2World& b2dworld, anax::World& anaxWorld) : m_mapLoader(&mapDirectory),
			m_box2dWorld(&b2dworld), m_anaxWorld(&anaxWorld){

		m_entityCreators["RopeBox"] = std::unique_ptr<GameEntityCreator>(new RopeBox());
		m_entityCreators["Rope"] = std::unique_ptr<GameEntityCreator>(new Rope());
		m_entityCreators["Boulder"] = std::unique_ptr<GameEntityCreator>(new Boulder());
		m_entityCreators["BladeShooter"] = std::unique_ptr<GameEntityCreator>(new BladeShooter());
		m_entityCreators["DeathFloor"] = std::unique_ptr<GameEntityCreator>(new DeathFloor());
		m_entityCreators["DynamicRotatingBlade"] = std::unique_ptr<GameEntityCreator>(new DynamicRotatingBlade());
		m_entityCreators["PlayerEndPoint"] = std::unique_ptr<GameEntityCreator>(new PlayerEndPoint());


	}

	~TmxBox2dLevelLoaderImpl() {}

	void loadSplittableObjects( tmx::MapObjects& mapObject){
		for (auto& object : mapObject) {
			m_splittableObjectCreator.createEntity(object, *m_box2dWorld, *m_anaxWorld);
		}
	}

	void loadStaticObjects(tmx::MapObjects& mapObject) {
		for (auto& object : mapObject) {
			m_staticObjectCreator.createEntity(object, *m_box2dWorld, *m_anaxWorld);
		}
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
				std::cerr << "No entity creator found for name: " << entityName << std::endl;
			}
		}
	}

	void loadInterestPoints(const tmx::MapObjects& mapObject, lua_State* luaState) {
		for (auto object : mapObject) {
			if (object.GetName() == "PlayerStartPoint") {
				m_playerEntityLoader.loadEntity(*m_anaxWorld, *m_box2dWorld, object, luaState);
			}else{
				loadEntities(mapObject);
			}
		}
	}

	void loadTmxLayerForLevel(tmx::MapLayer& layer, b2World& b2dworld, anax::World& anaxWorld, lua_State* luaState) {
		if (layer.name == "StaticObjects") {
			loadStaticObjects(layer.objects);
		} else if (layer.name == "SplittableObjects") {
			loadSplittableObjects(layer.objects);
		} else if (layer.name == "Entities") {
			loadEntities(layer.objects);
		} else if (layer.name == "InterestPoints") {
			loadInterestPoints(layer.objects, luaState);
		} else {
			auto objectsMap = loadMiscMapObjects(layer.objects);
		}
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

	void restartLevel(){
		unsigned int previousLevelIndex = m_currentLevelIndex - 1;
		loadLevel(previousLevelIndex);
	}


	void loadNextLevel(){
		loadLevel(m_currentLevelIndex);
		m_currentLevelIndex++;
	}

	void loadLevel(int levelNumberToLoad) {
	    lua_State *luaState = luaL_newstate();
	    luabind::open(luaState);
		luaL_openlibs(luaState);

		luabind::module(luaState)[
		luabind::class_<LevelObject>("LevelObject")
		      .def(luabind::constructor<>())
		      .def_readwrite("levelMapName", &LevelObject::levelMapName)
		      .def_readwrite("scriptName", &LevelObject::scriptName)
		];

		if(m_levelsToLoad.size() <= 0 && levelNumberToLoad <= 0){
			loadLevelList(luaState);
		}

		if(levelNumberToLoad < m_levelsToLoad.size()){
			auto entities = m_anaxWorld->getEntities();
			deleteEntitiesWithPhysicsComponents(entities);
			deleteAllBox2dBodies();
			deleteAllEntities(entities);
			std::cout << "After deleting all count is: " << m_box2dWorld->GetBodyCount() << std::endl;
			m_anaxWorld->refresh(); //Last thing refresh all entities doesn't matter if we refresh twice in one update since the level will be changed after draw

			m_mapLoader->Load(m_levelsToLoad[levelNumberToLoad].levelMapName);
			std::vector<tmx::MapLayer>& layers = m_mapLoader->GetLayers();
			const std::string t = "TexCoords";
			std::vector<tmx::MapObject> levelObjects;
			for (auto& layer : layers) {
				if (layer.visible) {
					loadTmxLayerForLevel(layer, *m_box2dWorld, *m_anaxWorld, luaState);
				}
			}

			for (auto& layer : layers) {
				levelObjects.insert(levelObjects.end(), layer.objects.begin(), layer.objects.end());
			}

			luaScriptLevel.reset(new LuaScriptLevel(*m_box2dWorld, m_levelsToLoad[levelNumberToLoad].scriptName));
			luaScriptLevel->loadLevel(levelObjects);
		}
		lua_close(luaState);
	}

	void deleteAllBox2dBodies() {
		b2Body* box2dBody = m_box2dWorld->GetBodyList();
		while (box2dBody) {
			m_box2dWorld->DestroyBody(box2dBody);
			box2dBody = box2dBody->GetNext();
		}
	}

	void deleteEntitiesWithPhysicsComponents(std::vector<anax::Entity>& entities){
		std::cout << "before deleteing all count is: " << m_box2dWorld->GetBodyCount() << std::endl;
		for(anax::Entity entity : entities){
			if(entity.hasComponent<PhysicsComponent>()){
				auto& physicsComp = entity.getComponent<PhysicsComponent>();
				if(physicsComp.physicsBody){
					delete(physicsComp.physicsBody->GetUserData());
					m_box2dWorld->DestroyBody(physicsComp.physicsBody);
				}
			}
		}
	}

	void deleteAllEntities(std::vector<anax::Entity>& entities){
		m_anaxWorld->killEntities(entities);
	}

	void update() {
		luaScriptLevel->updateLevel();
	}

	void BeginContact(b2Contact* contact) {
		luaScriptLevel->BeginContact(contact);

	}

	void EndContact(b2Contact* contact) {
		luaScriptLevel->EndContact(contact);

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

void TmxBox2dLevelLoader::restartLevel() {
	m_impl->restartLevel();
}

sf::Vector2u TmxBox2dLevelLoader::getMapSize() {
	return m_impl->getMapSize();
}
