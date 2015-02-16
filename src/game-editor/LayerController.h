#ifndef SRC_GAME_EDITOR_LAYERCONTROLLER_H_
#define SRC_GAME_EDITOR_LAYERCONTROLLER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <tmx/MapObject.h>
#include <unordered_map>
#include <boost/optional.hpp>
#include <anax/World.hpp>
#include <Box2D/Box2D.h>

enum LayerType {
	TILE, OBJECTS
};

class Layer {

public:
	struct LayerHasher
	{

		std::size_t operator()(Layer const& layer) const {
			std::size_t h1 = std::hash<std::string>()(layer.m_layerName);
			return h1;
		}
	};

	Layer(std::string layerName, LayerType layerType) : m_layerName(layerName), m_layerType(layerType){
	}

	~Layer(){}

	bool operator <(const Layer& rhs) const {
		return this->m_layerName < rhs.m_layerName;
	}

	bool operator ==(const Layer& other) const {
		return this->m_layerName == other.m_layerName;
	}

	const std::string getLayerName() const{
		return m_layerName;
	}

	LayerType getLayerType(){
		return m_layerType;
	}

private:
	std::string m_layerName;
	LayerType m_layerType;

};

class LayerController {
public:
	LayerController(anax::World& anaxWorld, b2World& box2dWorld);
	~LayerController();

	void addMapObjectToCurrentLayer(tmx::MapObject mapObject);
	void attachTo(sfg::Box::Ptr box);
	void addLayer(std::string layerName, LayerType layerType);
	boost::optional<Layer> getCurrentlySelectedLayer();
	void update(sf::Vector2i mousePos, std::vector<sf::Event>& events);

private:
	class LayerControllerImpl;
	std::unique_ptr<LayerControllerImpl> m_impl;

};

#endif /* SRC_GAME_EDITOR_LAYERCONTROLLER_H_ */
