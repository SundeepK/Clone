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
#include <game-objects/RopeBox.h>
#include <game-objects/GameEntityCreator.h>
#include <game-objects/Rope.h>
#include <game-objects/Boulder.h>
#include <boost/algorithm/string.hpp>
#include <game-objects/GameObjectTag.h>
#include <components/NinjaDataComponent.h>
#include <game-objects/BladeShooter.h>
#include <components/Direction.h>

class TmxBox2dLevelLoader::TmxBox2dLevelLoaderImpl{
public:

	std::unique_ptr<tmx::MapLoader> m_mapLoader;
	std::unique_ptr<b2World> m_box2dWorld;
	std::unique_ptr<anax::World> m_anaxWorld;
	std::vector<LevelObject> m_levelsToLoad;
	WorldEntityLoader m_worldEntityLoader;
	std::unordered_map<std::string, tmx::MapObject> m_levelObjects;
	unsigned int m_currentLevelIndex = 0;
	std::unique_ptr<LuaScriptLevel> luaScriptLevel;
	std::unordered_map<std::string, std::unique_ptr<GameEntityCreator>> m_entityCreators;

	TmxBox2dLevelLoaderImpl(tmx::MapLoader& mapDirectory, b2World& b2dworld, anax::World& anaxWorld) : m_mapLoader(&mapDirectory),
			m_box2dWorld(&b2dworld), m_anaxWorld(&anaxWorld){

		m_entityCreators["RopeBox"] = std::unique_ptr<GameEntityCreator>(new RopeBox());
		m_entityCreators["Rope"] = std::unique_ptr<GameEntityCreator>(new Rope());
		m_entityCreators["Boulder"] = std::unique_ptr<GameEntityCreator>(new Boulder());
		m_entityCreators["BladeShooter"] = std::unique_ptr<GameEntityCreator>(new BladeShooter());

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
			 //TODO Handle exception if texcoord cant be parsed
			 float value = std::stof(texCoord);
			 if(count % 2 == 0){
				 textureCoords.push_back(b2Vec2(x, value));
			 }else{
				x = value;
			 }
		 }
		 return textureCoords;
	}

	std::unordered_map<std::string, tmx::MapObject> loadSplittableObjects( tmx::MapObjects& mapObject, anax::World& anaxWorld, b2World& b2dworld){
		std::unordered_map<std::string, tmx::MapObject> mapObjects;
		for (auto& object : mapObject) {

			if (!object.GetName().empty()) {
				mapObjects.insert(std::pair<std::string, tmx::MapObject>(object.GetName(), object));
			}

			auto objectEntity = anaxWorld.createEntity();
			auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
			auto& splitDirectionComp = objectEntity.addComponent<SplitDirectionComponent>();
			auto& physComp = objectEntity.addComponent<PhysicsComponent>();
			auto& ninjaData = objectEntity.addComponent<NinjaDataComponent>();


			if (!texCoordsComp.image.loadFromFile("maps/" + object.GetPropertyString("Texture")))
				std::cout << "unable to load texture from tmx: " <<  object.GetPropertyString("Texture") << std::endl;
			texCoordsComp.image.flipVertically();
			texCoordsComp.textCoords = parseTexCoordsFromTmxObject(object.GetPropertyString("TexCoords"));

			texCoordsComp.texture = TextureLoader::loadAsOpenglTexture(texCoordsComp.texture, texCoordsComp.image);
			std::cout << object.PolyPoints().size() << "points size" << std::endl;

			if (object.GetPropertyString("Body") == "dynamic") {
				physComp.physicsBody = tmx::BodyCreator::Add(object, b2dworld, b2_dynamicBody);
			} else {
				physComp.physicsBody = tmx::BodyCreator::Add(object, b2dworld, b2_staticBody);
			}

			b2Filter filter;
			filter.categoryBits = GameObjectTag::SPLITTABLE_OBJECT;;
			physComp.physicsBody->GetFixtureList()->SetFilterData(filter);

			splitDirectionComp.splitDirection = DirectionMap::parseDirection(object.GetPropertyString("SplitDir"));

			objectEntity.activate();
		}
		return mapObjects;
	}

	std::unordered_map<std::string, tmx::MapObject> loadStaticObjects(tmx::MapObjects& mapObject, b2World& b2dworld) {
		std::unordered_map<std::string, tmx::MapObject> mapObjects;
		for (auto& object : mapObject) {
			if (!object.GetName().empty()) {
				mapObjects.insert(std::pair<std::string, tmx::MapObject>(object.GetName(), object));
			}

			if (object.GetPropertyString("Body") == "dynamic") {
				 tmx::BodyCreator::Add(object, b2dworld, b2_dynamicBody);
			} else {
				 tmx::BodyCreator::Add(object, b2dworld, b2_staticBody);
			}

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
			deleteEntitiesWithPhysicsComponents(entities);
			deleteAllBox2dBodies();
			deleteAllEntities(entities);

			m_mapLoader->Load(m_levelsToLoad[m_currentLevelIndex].levelMapName);
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
		luaScriptLevel.reset(new LuaScriptLevel(*m_box2dWorld, m_levelsToLoad[m_currentLevelIndex].scriptName));
		luaScriptLevel->loadLevel(m_levelObjects);
		m_currentLevelIndex++;

	}

	void deleteAllBox2dBodies() {
		b2Body* box2dBody = m_box2dWorld->GetBodyList();
		while (box2dBody) {
			m_box2dWorld->DestroyBody(box2dBody);
			box2dBody = box2dBody->GetNext();
		}
	}

	void deleteEntitiesWithPhysicsComponents(std::vector<anax::Entity>& entities){
		std::cout << "beofer deleteing all count is: " << m_box2dWorld->GetBodyCount() << std::endl;
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
