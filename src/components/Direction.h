#ifndef SRC_COMPONENTS_DIRECTION_H_
#define SRC_COMPONENTS_DIRECTION_H_

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <unordered_map>

enum class Direction {
		RIGHT,
		LEFT,
		TOP,
		DOWN,
		NONE
};

class DirectionMap{
public:

	static const std::unordered_map<std::string, Direction> DIRECTION_MAP;
	static Direction parseDirection(std::string direction);
};



#endif /* SRC_COMPONENTS_DIRECTION_H_ */
