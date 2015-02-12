#include <game-editor/LayerController.h>

struct LayerControllerContainer {

	std::vector<sfg::Label::Ptr> objectLabels;
	std::vector<sfg::CheckButton::Ptr> checkButtons;

};

class LayerController::LayerControllerImpl{
public:

	sfg::Table::Ptr m_objectCreatorTable;
	sfg::ComboBox::Ptr m_gameObjectsComboBox;
	sfg::Box::Ptr m_objectLabelBox;
	sfg::Box::Ptr m_objectCheckButtonBox;
	std::unordered_map<Layer, std::vector<tmx::MapObject>, Layer::LayerHasher> m_layerToMapObjects;

	LayerControllerImpl(){
		m_objectCreatorTable = sfg::Table::Create();
		m_gameObjectsComboBox = sfg::ComboBox::Create();
		m_objectLabelBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_objectCheckButtonBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_objectCreatorTable->Attach( m_gameObjectsComboBox, sf::Rect<sf::Uint32>( 0, 0, 2, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
		m_objectCreatorTable->Attach( m_objectCheckButtonBox, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), 0, sfg::Table::FILL);
		m_objectCreatorTable->Attach( m_objectLabelBox, sf::Rect<sf::Uint32>( 1, 1, 1, 1 ), 0, sfg::Table::FILL);
		addLayer("TileLayer", LayerType::TILE);
		m_gameObjectsComboBox->SelectItem(0);
	}

	~LayerControllerImpl(){}

	void attachTo(sfg::Box::Ptr box){
		box->Pack( m_objectCreatorTable, false );
	}

	void addMapObjectToCurrentLayer(tmx::MapObject mapObject) {
		auto layerName = static_cast<std::string>(m_gameObjectsComboBox->GetSelectedText());

		if (layerName.empty()) {
			return;
		}

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

};

LayerController::LayerController() : m_impl(new LayerControllerImpl()){
}

LayerController::~LayerController() {
}

void LayerController::attachTo(sfg::Box::Ptr box) {
	m_impl->attachTo(box);
}

void LayerController::addMapObjectToCurrentLayer(tmx::MapObject mapObject) {
	m_impl->addMapObjectToCurrentLayer(mapObject);
}

void LayerController::addLayer(std::string layerName, LayerType layerType) {
	m_impl->addLayer(layerName, layerType);
}

boost::optional<Layer> LayerController::getCurrentlySelectedLayer() {
	return m_impl->getCurrentlySelectedLayer();
}
