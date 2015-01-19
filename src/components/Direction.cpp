#include <components/Direction.h>

const std::unordered_map<std::string, Direction> DirectionMap::DIRECTION_MAP = {
		{"right", Direction::RIGHT},
		{"left", Direction::LEFT},
		{"top", Direction::TOP},
		{"down", Direction::DOWN},
		{"none", Direction::NONE}
};


Direction DirectionMap::parseDirection(std::string direction) {
	boost::algorithm::to_lower(direction);
	auto splitDirection =  DirectionMap::DIRECTION_MAP.find(direction);
	std::cout << "dir: " << direction << std::endl;
	assert (
		"Split direction is not found" &&
		splitDirection != DirectionMap::DIRECTION_MAP.end()
	);
	return splitDirection->second;
}





