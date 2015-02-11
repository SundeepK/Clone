#include <game-editor/ObjectCreatorController.h>
#include <unordered_map>
#include <iostream>

struct ObjectCreatorContainer{

	std::vector<sfg::Label::Ptr> propertyLabels;
	std::vector<sfg::Entry::Ptr> propertyEntryBoxes;

};

class ObjectCreatorController::ObjectCreatorControllerImpl{
public:

	ObjectCreatorControllerImpl(anax::World& anaxWorld, b2World& box2dWorld) : m_anaxWorld(&anaxWorld), m_box2dWorld(&box2dWorld){
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

	std::unique_ptr<anax::World> m_anaxWorld;
	std::unique_ptr<b2World> m_box2dWorld;
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

		createGameObjectWithCurrentlySelectedObjectCreator(sf::Vector2f(50.0f, 50.0f));
	}

	void attachTo(sfg::Box::Ptr table){
		table->Pack( m_objectCreatorTable, false );
		table->ReorderChild(m_objectCreatorTable, 0);
//		table->Attach(m_gameObjectsComboBox, sf::Rect<sf::Uint32>(  2, 1, 1, 1 ), sfg::Table::FILL, 0 );
	}

	void createGameObjectWithCurrentlySelectedObjectCreator(sf::Vector2f position) {
		auto gameObjectItr = m_entityCreators.find(m_currentObjectCreator);
		if (gameObjectItr != m_entityCreators.end()) {
			tmx::MapObject mapObject;
			mapObject.SetPosition(position);
			for(auto entry : m_objectCreatorContainer.propertyEntryBoxes){
				mapObject.SetProperty(entry->GetId(), "5");
			}
			gameObjectItr->second->createEntity(mapObject, *m_box2dWorld, *m_anaxWorld);
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

void ObjectCreatorController::createGameObjectAt(sf::Vector2f& position) {
	m_impl->createGameObjectWithCurrentlySelectedObjectCreator(position);
}
