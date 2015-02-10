#include <game-editor/ObjectCreatorController.h>
#include <unordered_map>
#include <iostream>

struct ObjectCreatorContainer{

	std::vector<sfg::Label::Ptr> propertyLabels;
	std::vector<sfg::Entry::Ptr> propertyEntryBoxes;

};

class ObjectCreatorController::ObjectCreatorControllerImpl{
public:

	ObjectCreatorControllerImpl(){
		m_objectCreatorTable = sfg::Table::Create();
		m_inputBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_labelBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_gameObjectsComboBox = sfg::ComboBox::Create();
		m_gameObjectsComboBox->AppendItem( L"test");
		m_inputBox->Pack(m_gameObjectsComboBox, false);
	//	m_gameObjectsComboBox->GetSignal( sfg::ComboBox::OnSelect ).Connect( std::bind( &ObjectCreatorControllerImpl::onObjectCreatorSelect, this ) );
	//	m_objectCreatorTable->Attach( m_gameObjectsComboBox, sf::Rect<sf::Uint32>( 0, 0, 2, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
		m_objectCreatorTable->Attach( m_labelBox, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), 0, sfg::Table::FILL);
		m_objectCreatorTable->Attach( m_inputBox, sf::Rect<sf::Uint32>( 1, 1, 1, 1 ), 0, sfg::Table::FILL);
	}

	~ObjectCreatorControllerImpl(){}

	sfg::Table::Ptr m_objectCreatorTable;
	sfg::Box::Ptr m_inputBox;
	sfg::Box::Ptr m_labelBox;
	sfg::ComboBox::Ptr m_gameObjectsComboBox;
	std::unordered_map<std::string, std::unique_ptr<GameEntityCreator>> m_entityCreators;
	ObjectCreatorContainer m_objectCreatorContainer;

	void addEntityCreator(std::string nameOfObjectCreator, std::unique_ptr<GameEntityCreator> entityCreator) {
		m_entityCreators.insert(std::make_pair(nameOfObjectCreator, std::move(entityCreator)));
		m_gameObjectsComboBox->AppendItem(nameOfObjectCreator);
	}

	void onObjectCreatorSelect() {
		auto selectedGameObjectName = static_cast<std::string>(m_gameObjectsComboBox->GetSelectedText());
		auto gameObjectItr = m_entityCreators.find(selectedGameObjectName);
		if (gameObjectItr != m_entityCreators.end()) {
			std::cout << "on select " << gameObjectItr->first << std::endl;
			m_objectCreatorContainer.propertyEntryBoxes.clear();
			m_objectCreatorContainer.propertyLabels.clear();
			m_inputBox->RemoveAll();
			m_labelBox->RemoveAll();

		    auto propertyNames =  gameObjectItr->second->getProperties();
			for (auto property : propertyNames) {
				auto label = sfg::Label::Create(property);
				m_objectCreatorContainer.propertyLabels.push_back(label);
				m_labelBox->Pack(label, false);
			}
			m_labelBox->Invalidate();
		}
	}

	void attachTo(sfg::Table::Ptr table){
//		table->Attach(m_gameObjectsComboBox, sf::Rect<sf::Uint32>(  2, 0, 1, 1 ), sfg::Table::FILL, 0 );
		table->Attach( m_inputBox, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );

	}

};

ObjectCreatorController::ObjectCreatorController() : m_impl(new ObjectCreatorControllerImpl()){

}

ObjectCreatorController::~ObjectCreatorController() {
}

void ObjectCreatorController::addEntityCreator(std::string nameOfCreator, std::unique_ptr<GameEntityCreator> entityCreator) {
	m_impl->addEntityCreator(nameOfCreator, std::move(entityCreator));
}

void ObjectCreatorController::attachTo(sfg::Table::Ptr window) {
	m_impl->attachTo(window);
}
