#include <game-editor/LayerController.h>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <components/IDComponent.h>
#include <components/SizeComponent.h>
#include <components/PhysicsComponent.h>
#include <iostream>
#include <tmx/tmx2box2d.h>
#include <components/AABBComponent.h>
#include <game-editor/ObjectCreatorController.h>
#include <game-objects/GameEntityCreator.h>
#include <game-objects/Boulder.h>
#include <game-objects/Rope.h>

struct LayerControllerContainer {

	std::vector<sfg::Label::Ptr> objectLabels;
	std::vector<sfg::CheckButton::Ptr> checkButtons;

};

class LayerController::LayerControllerImpl{
public:


	anax::World& m_anaxWorld;
	b2World& m_box2dWorld;
	sfg::Table::Ptr m_objectCreatorTable;
	sfg::ToggleButton::Ptr m_selectToolButton;
	sfg::ComboBox::Ptr m_gameObjectsComboBox;
	sfg::Box::Ptr m_objectLabelBox;
	sfg::Box::Ptr m_objectCheckButtonBox;
	std::unordered_map<Layer, std::vector<tmx::MapObject>, Layer::LayerHasher> m_layerToMapObjects;
	std::string m_uuidOfSelectedObjectForDeletion;
	sf::Image m_selectToolImage;
	sfg::Image::Ptr m_sfguiSelectToolImage;
	sf::RectangleShape m_objectBoundsRect;
	ObjectCreatorController m_objectController;


	LayerControllerImpl(anax::World& anaxWorld, b2World& box2dWorld) : m_anaxWorld(anaxWorld), m_box2dWorld(box2dWorld),  m_objectController(anaxWorld, box2dWorld) {
		m_objectCreatorTable = sfg::Table::Create();
		m_gameObjectsComboBox = sfg::ComboBox::Create();
		m_objectLabelBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_objectCheckButtonBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_selectToolButton = sfg::ToggleButton::Create();
		m_selectToolImage.loadFromFile("icons/tool-select-objects.png");
		m_sfguiSelectToolImage = sfg::Image::Create();
		m_sfguiSelectToolImage->SetImage(m_selectToolImage);
		m_selectToolButton->SetImage(m_sfguiSelectToolImage);
		m_objectCreatorTable->Attach( m_gameObjectsComboBox, sf::Rect<sf::Uint32>( 0, 0, 2, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
		m_objectCreatorTable->Attach( m_objectCheckButtonBox, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), 0, sfg::Table::FILL);
		m_objectCreatorTable->Attach( m_objectLabelBox, sf::Rect<sf::Uint32>( 1, 1, 1, 1 ), 0, sfg::Table::FILL);
		m_objectCreatorTable->Attach( m_selectToolButton, sf::Rect<sf::Uint32>( 0, 2, 1, 1 ), 0, sfg::Table::FILL);
		addLayer("TileLayer", LayerType::TILE);
		m_gameObjectsComboBox->SelectItem(0);

		m_objectController.addEntityCreator("boulder", std::unique_ptr<GameEntityCreator>(new Boulder()));
		m_objectController.addEntityCreator("rope", std::unique_ptr<GameEntityCreator>(new Rope()));

		m_objectBoundsRect.setFillColor(sf::Color(250, 77, 100, 150));
		m_objectBoundsRect.setOutlineThickness(2.0f);
		m_objectBoundsRect.setOutlineColor(sf::Color::Red);
	}

	~LayerControllerImpl(){}

	void attachTo(sfg::Box::Ptr box){
		box->Pack( m_objectCreatorTable, false );
		m_objectController.attachTo(box);
	}

	void update(sf::Vector2i mousePos, std::vector<sf::Event>& events) {
		if (m_selectToolButton->IsActive()) {
			for (auto event : events) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					selectedObjectForDeletion(mousePos);
				} else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Delete) {
						deleteCurrentlySelectedObject();
					}
				}

			}
		}
	}

	void selectedObjectForDeletion(sf::Vector2i mousePos) {
		auto entities = m_anaxWorld.getEntities();
		sf::IntRect testRect;
		std::string uuid;
		for (auto entity : entities) {
			if (entity.hasComponent<IDComponent>() && entity.hasComponent<PhysicsComponent>()) {
				auto idComponent = entity.getComponent<IDComponent>();
				auto physicsComponent = entity.getComponent<PhysicsComponent>();
				auto physicsBody = physicsComponent.physicsBody;
				auto position = tmx::BoxToSfVec(physicsBody->GetPosition());

				if (entity.hasComponent<AABBComponent>()) {
					auto aabbComponent = entity.getComponent<AABBComponent>();
					testRect.left = aabbComponent.aabb.left;
					testRect.top = aabbComponent.aabb.top;
					testRect.height =  aabbComponent.aabb.height;
					testRect.width =aabbComponent.aabb.width;

				}else if (entity.hasComponent<SizeComponent>()) {
					auto sizeComponent = entity.getComponent<SizeComponent>();
					testRect.left = position.x;
					testRect.top = position.y;
					testRect.width = sizeComponent.size.x;
					testRect.height = sizeComponent.size.y;
				}

				if (testRect.contains(mousePos)) {
					m_objectBoundsRect.setPosition(sf::Vector2f(testRect.left,testRect.top));
					m_objectBoundsRect.setSize(sf::Vector2f(testRect.width, testRect.height));
					m_uuidOfSelectedObjectForDeletion = idComponent.uuid;
					break;
				}

			}
		}
	}

	void deleteCurrentlySelectedObject(){
		auto entities = m_anaxWorld.getEntities();
		for (auto entity : entities) {
			if (entity.hasComponent<IDComponent>() && entity.hasComponent<PhysicsComponent>()) {
				auto idComponent = entity.getComponent<IDComponent>();
				auto physicsBody = entity.getComponent<PhysicsComponent>().physicsBody;
				if (idComponent.uuid == m_uuidOfSelectedObjectForDeletion) {
					m_box2dWorld.DestroyBody(physicsBody);
					entity.kill();
					m_objectBoundsRect.setSize(sf::Vector2f(0,0));
				}
			}
		}
	}

	void addMapObjectToCurrentLayerWithAABB(sf::IntRect objectBounds) {
		auto layerName = static_cast<std::string>(m_gameObjectsComboBox->GetSelectedText());

		if (layerName.empty()) {
			return;
		}

		if(m_selectToolButton->IsActive()){
			return;
		}

		auto mapObject = m_objectController.createGameObjectAt(objectBounds);

		for(auto mapItr=m_layerToMapObjects.begin(); mapItr!=m_layerToMapObjects.end(); ++mapItr) {
			if (mapItr->first.getLayerName() == layerName) {
				mapItr->second.push_back(mapObject);
			}
			break;
		}
	}

	void addLayer(std::string layerName, LayerType layerType) {
		Layer layer(layerName, layerType);
		auto layerToMapObjectsItr = m_layerToMapObjects.find(layer);

		if (layerToMapObjectsItr == m_layerToMapObjects.end()) {
			std::vector<tmx::MapObject> mapObjects;
			Layer layer(layerName, layerType);
			m_layerToMapObjects.insert(std::make_pair(layer, mapObjects));
			m_gameObjectsComboBox->AppendItem(layerName);
		}

	}

	boost::optional<Layer> getCurrentlySelectedLayer() {
		auto layerName = static_cast<std::string>(m_gameObjectsComboBox->GetSelectedText());
		for (auto mapItr = m_layerToMapObjects.begin(); mapItr != m_layerToMapObjects.end(); ++mapItr) {
			if (mapItr->first.getLayerName() == layerName) {
				auto layer = mapItr->first;
				return boost::optional<Layer>(layer);
			}
		}
		return boost::optional<Layer>();
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		rt.draw(m_objectBoundsRect);
	}

};

LayerController::LayerController(anax::World& anaxWorld, b2World& box2dWorld) : m_impl(new LayerControllerImpl(anaxWorld, box2dWorld)){
}

LayerController::~LayerController() {
}

void LayerController::attachTo(sfg::Box::Ptr box) {
	m_impl->attachTo(box);
}

void LayerController::addMapObjectToCurrentLayerWithAABB(sf::IntRect objectBounds) {
	m_impl->addMapObjectToCurrentLayerWithAABB(objectBounds);
}

void LayerController::addLayer(std::string layerName, LayerType layerType) {
	m_impl->addLayer(layerName, layerType);
}

boost::optional<Layer> LayerController::getCurrentlySelectedLayer() {
	return m_impl->getCurrentlySelectedLayer();
}

void LayerController::update(sf::Vector2i mousePos, std::vector<sf::Event>& events) {
	m_impl->update(mousePos, events);
}

void LayerController::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}
