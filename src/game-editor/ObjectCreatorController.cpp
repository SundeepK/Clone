#include <game-editor/ObjectCreatorController.h>
#include <unordered_map>
#include <iostream>
#include <UUIDGenerator.h>
#include <entity-loaders/PlayerEntityLoader.h>

struct ObjectCreatorContainer{

	std::vector<sfg::Label::Ptr> propertyLabels;
	std::vector<sfg::Entry::Ptr> propertyEntryBoxes;

};

class ObjectCreatorController::ObjectCreatorControllerImpl{
public:

	anax::World& m_anaxWorld;
	b2World& m_box2dWorld;
	sfg::Table::Ptr m_objectCreatorTable;
	sfg::Box::Ptr m_inputBox;
	sfg::Box::Ptr m_labelBox;
	sfg::ComboBox::Ptr m_gameObjectsComboBox;
	std::unordered_map<std::string, std::unique_ptr<GameEntityCreator>> m_entityCreators;
	std::unordered_map<std::string, sf::Color> m_entityCreatorToLayerColors;
	ObjectCreatorContainer m_objectCreatorContainer;
	PlayerEntityLoader m_playerLoader;

	std::string m_currentObjectCreator;

	ObjectCreatorControllerImpl(anax::World& anaxWorld, b2World& box2dWorld) : m_anaxWorld(anaxWorld), m_box2dWorld(box2dWorld){
		m_objectCreatorTable = sfg::Table::Create();
		m_inputBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_labelBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_gameObjectsComboBox = sfg::ComboBox::Create();
		m_gameObjectsComboBox->GetSignal( sfg::ComboBox::OnSelect ).Connect( std::bind( &ObjectCreatorControllerImpl::onObjectCreatorSelect, this ) );
		m_objectCreatorTable->Attach( m_gameObjectsComboBox, sf::Rect<sf::Uint32>( 0, 0, 2, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
		m_objectCreatorTable->Attach( m_labelBox, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), 0, sfg::Table::FILL);
		m_objectCreatorTable->Attach( m_inputBox, sf::Rect<sf::Uint32>( 1, 1, 1, 1 ), 0, sfg::Table::FILL);
		m_gameObjectsComboBox->AppendItem("player");

	}

	~ObjectCreatorControllerImpl(){}


	void addEntityCreator(std::string nameOfObjectCreator, std::unique_ptr<GameEntityCreator> entityCreator) {
		m_entityCreators.insert(std::make_pair(nameOfObjectCreator, std::move(entityCreator)));
		m_entityCreatorToLayerColors.insert(std::make_pair(nameOfObjectCreator, randColor()));
		m_gameObjectsComboBox->AppendItem(nameOfObjectCreator);
	}

	tmx::MapObject addPlayer(sf::IntRect aabb){
		tmx::MapObject mapObject;
		mapObject.SetProperty("uuid", UUIDGenerator::createUuid());
		mapObject.SetPosition(sf::Vector2f(aabb.left, aabb.top));
		mapObject.SetSize(sf::Vector2f(aabb.width, aabb.height));
		mapObject.SetProperty("layerColor",  "255, 41, 105");
		mapObject.SetProperty("objectType", "player");
		mapObject.SetPosition(sf::Vector2f(aabb.left, aabb.top));
		mapObject.AddPoint(sf::Vector2f(0,0));
		mapObject.AddPoint(sf::Vector2f(aabb.width, 0));
		mapObject.AddPoint(sf::Vector2f(aabb.width, aabb.height));
		mapObject.AddPoint(sf::Vector2f(0, aabb.height));
		mapObject.CreateDebugShape(sf::Color::Blue);
		lua_State *luaState = luaL_newstate();
	    luabind::open(luaState);
		luaL_openlibs(luaState);
		m_playerLoader.loadEntity(m_anaxWorld, m_box2dWorld, mapObject, luaState);
		lua_close(luaState);
		return mapObject;
	}

	sf::Color randColor()
	{
	    return sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
	}

	void onObjectCreatorSelect() {
		m_currentObjectCreator = static_cast<std::string>(m_gameObjectsComboBox->GetSelectedText());
		auto gameObjectItr = m_entityCreators.find(m_currentObjectCreator);
		if (gameObjectItr != m_entityCreators.end()) {
			m_objectCreatorContainer.propertyEntryBoxes.clear();
			m_objectCreatorContainer.propertyLabels.clear();
			m_inputBox->RemoveAll();
			m_labelBox->RemoveAll();

		    auto objectProperties =  gameObjectItr->second->getProperties().properties;
			for(auto objectProperty = objectProperties.begin(); objectProperty !=objectProperties.end(); ++objectProperty ) {
				auto propertyName = objectProperty->first;
				auto label = sfg::Label::Create(propertyName);
				auto entry = sfg::Entry::Create();
				entry->SetRequisition( sf::Vector2f( 150.f, 0.f ) );
				m_objectCreatorContainer.propertyLabels.push_back(label);
				m_objectCreatorContainer.propertyEntryBoxes.push_back(entry);
				entry->SetId(propertyName);
				entry->SetText(objectProperty->second);
				entry->SetMaximumLength(500);
				label->SetAlignment(sf::Vector2f(2, 2));
				m_labelBox->Pack(label, true);
				m_inputBox->Pack(entry, true, true);
			}
			m_labelBox->Invalidate();
		}
	}

	void attachTo(sfg::Box::Ptr table){
		table->Pack( m_objectCreatorTable, false );
	}

	tmx::MapObject addGameObject(sf::IntRect aabb) {
		tmx::MapObject mapObject;

		if(aabb.height < 5 && aabb.width < 5){
			return mapObject;
		}

		auto gameObjectItr = m_entityCreators.find(m_currentObjectCreator);
		if (gameObjectItr != m_entityCreators.end()) {
			mapObject.SetProperty("uuid", UUIDGenerator::createUuid());
			auto color = m_entityCreatorToLayerColors[m_currentObjectCreator];
			std::string stringColor = std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b);

			auto gameObjectProperty = gameObjectItr->second->getProperties();
			if (gameObjectProperty.hasShape) {
				mapObject.SetShapeType(gameObjectProperty.objectShapeType);
			}
			mapObject.SetSize(sf::Vector2f(aabb.width, aabb.height));
			mapObject.SetProperty("layerColor", stringColor);
			mapObject.SetProperty("objectType", m_currentObjectCreator);
			mapObject.SetPosition(sf::Vector2f(aabb.left, aabb.top));
			mapObject.AddPoint(sf::Vector2f(0, 0));
			mapObject.AddPoint(sf::Vector2f(aabb.width, 0));
			mapObject.AddPoint(sf::Vector2f(aabb.width, aabb.height));
			mapObject.AddPoint(sf::Vector2f(0, aabb.height));
			mapObject.CreateDebugShape(sf::Color::Blue);
			for (auto entry : m_objectCreatorContainer.propertyEntryBoxes) {
				mapObject.SetProperty(static_cast<std::string>(entry->GetId()), static_cast<std::string>(entry->GetText()));
			}
			gameObjectItr->second->createEntity(mapObject, m_box2dWorld, m_anaxWorld);
		}
		return mapObject;
	}

	tmx::MapObject createGameObjectWithCurrentlySelectedObjectCreator(sf::IntRect aabb) {
		if(m_currentObjectCreator == "player"){
			return addPlayer(aabb);
		}else{
			return addGameObject(aabb);
		}
	}

};

ObjectCreatorController::ObjectCreatorController(anax::World& anaxWorld, b2World& box2dWorld) : m_impl(new ObjectCreatorControllerImpl(anaxWorld, box2dWorld)){

}

ObjectCreatorController::~ObjectCreatorController() {
}

void ObjectCreatorController::addEntityCreator(std::string nameOfCreator, std::unique_ptr<GameEntityCreator> entityCreator) {
	m_impl->addEntityCreator(nameOfCreator, std::move(entityCreator));
}

void ObjectCreatorController::attachTo(sfg::Box::Ptr window) {
	m_impl->attachTo(window);
}

tmx::MapObject ObjectCreatorController::createGameObjectAt(sf::IntRect aabb) {
	return m_impl->createGameObjectWithCurrentlySelectedObjectCreator(aabb);
}
