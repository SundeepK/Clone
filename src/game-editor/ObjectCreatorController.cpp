#include <game-editor/ObjectCreatorController.h>
#include <unordered_map>
#include <iostream>
#include <UUIDGenerator.h>

struct ObjectCreatorContainer{

	std::vector<sfg::Label::Ptr> propertyLabels;
	std::vector<sfg::Entry::Ptr> propertyEntryBoxes;

};

class ObjectCreatorController::ObjectCreatorControllerImpl{
public:

	ObjectCreatorControllerImpl(anax::World& anaxWorld, b2World& box2dWorld) : m_anaxWorld(anaxWorld), m_box2dWorld(box2dWorld){
		m_objectCreatorTable = sfg::Table::Create();
		m_inputBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_labelBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_gameObjectsComboBox = sfg::ComboBox::Create();
		m_gameObjectsComboBox->GetSignal( sfg::ComboBox::OnSelect ).Connect( std::bind( &ObjectCreatorControllerImpl::onObjectCreatorSelect, this ) );
		m_objectCreatorTable->Attach( m_gameObjectsComboBox, sf::Rect<sf::Uint32>( 0, 0, 2, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
		m_objectCreatorTable->Attach( m_labelBox, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), 0, sfg::Table::FILL);
		m_objectCreatorTable->Attach( m_inputBox, sf::Rect<sf::Uint32>( 1, 1, 1, 1 ), 0, sfg::Table::FILL);
	}

	~ObjectCreatorControllerImpl(){}

	anax::World& m_anaxWorld;
	b2World& m_box2dWorld;
	sfg::Table::Ptr m_objectCreatorTable;
	sfg::Box::Ptr m_inputBox;
	sfg::Box::Ptr m_labelBox;
	sfg::ComboBox::Ptr m_gameObjectsComboBox;
	std::unordered_map<std::string, std::unique_ptr<GameEntityCreator>> m_entityCreators;
	ObjectCreatorContainer m_objectCreatorContainer;
	std::string m_currentObjectCreator;

	void addEntityCreator(std::string nameOfObjectCreator, std::unique_ptr<GameEntityCreator> entityCreator) {
		m_entityCreators.insert(std::make_pair(nameOfObjectCreator, std::move(entityCreator)));
		m_gameObjectsComboBox->AppendItem(nameOfObjectCreator);
	}

	void onObjectCreatorSelect() {
		m_currentObjectCreator = static_cast<std::string>(m_gameObjectsComboBox->GetSelectedText());
		auto gameObjectItr = m_entityCreators.find(m_currentObjectCreator);
		if (gameObjectItr != m_entityCreators.end()) {
			m_objectCreatorContainer.propertyEntryBoxes.clear();
			m_objectCreatorContainer.propertyLabels.clear();
			m_inputBox->RemoveAll();
			m_labelBox->RemoveAll();

		    auto propertyNames =  gameObjectItr->second->getProperties();
			for (auto property : propertyNames) {
				auto label = sfg::Label::Create(property);
				auto entry = sfg::Entry::Create();
				entry->SetRequisition( sf::Vector2f( 80.f, 0.f ) );
				m_objectCreatorContainer.propertyLabels.push_back(label);
				m_objectCreatorContainer.propertyEntryBoxes.push_back(entry);
				entry->SetId(property);
				m_labelBox->Pack(label, true);
				m_inputBox->Pack(entry, false, true);
			}
			m_labelBox->Invalidate();
		}
	}

	void attachTo(sfg::Box::Ptr table){
		table->Pack( m_objectCreatorTable, false );
//		table->Attach(m_gameObjectsComboBox, sf::Rect<sf::Uint32>(  2, 1, 1, 1 ), sfg::Table::FILL, 0 );
	}

	tmx::MapObject createGameObjectWithCurrentlySelectedObjectCreator(sf::IntRect aabb) {
		tmx::MapObject mapObject;
		auto gameObjectItr = m_entityCreators.find(m_currentObjectCreator);
		if (gameObjectItr != m_entityCreators.end()) {
			mapObject.SetProperty("uuid", UUIDGenerator::createUuid());
			mapObject.SetPosition(sf::Vector2f(aabb.left, aabb.top));
			mapObject.AddPoint(sf::Vector2f(0,0));
			mapObject.AddPoint(sf::Vector2f(aabb.width, 0));
			mapObject.AddPoint(sf::Vector2f(aabb.width, aabb.height));
			mapObject.AddPoint(sf::Vector2f(0, aabb.height));
			mapObject.CreateDebugShape(sf::Color::Blue);
			for (auto entry : m_objectCreatorContainer.propertyEntryBoxes) {
//				std::cout << "now adding game object at x" << position.x <<  " y:" << position.y <<  "with property: " << static_cast<std::string>(entry->GetId()) << " " << static_cast<std::string>(entry->GetVisibleText()) << std::endl;
				mapObject.SetProperty(static_cast<std::string>(entry->GetId()), static_cast<std::string>(entry->GetVisibleText()));
			}
			gameObjectItr->second->createEntity(mapObject, m_box2dWorld, m_anaxWorld);
		}
		return mapObject;
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
