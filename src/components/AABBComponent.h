#ifndef SRC_COMPONENTS_AABBCOMPONENT_H_
#define SRC_COMPONENTS_AABBCOMPONENT_H_

#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>

class AABBComponent: public anax::Component<AABBComponent> {

public:
	sf::IntRect aabb;
	std::string stringColor = "0,0,0";
	sf::Color getColor();

private:
	sf::Color color;
	bool hasParsedColor = false;

};

inline sf::Color AABBComponent::getColor() {
	if(!hasParsedColor){
		 std::stringstream colorStream(stringColor);
		 std::vector<int> rgb;
		 std::string v;
		 while(std::getline(colorStream,v,',')){
			 //TODO Handle exception if color cant be parsed
			 int value = std::stof(v);
			 rgb.push_back(value);
		 }
		 color.r = rgb[0];
		 color.g = rgb[1];
		 color.b = rgb[2];
		 hasParsedColor = true;
		 return color;
	}else{
		return color;
	}
}

#endif /* SRC_COMPONENTS_AABBCOMPONENT_H_ */
