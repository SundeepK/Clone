#ifndef SPLITDIRECTION_H_
#define SPLITDIRECTION_H_

#include <anax/Component.hpp>

enum class SplitDirection {
		RIGHT,
		LEFT,
		TOP,
		DOWN
};


class SplitDirectionComponent : public anax::Component<SplitDirectionComponent>{

public:
	SplitDirection splitDirection;

};

#endif /* SPLITDIRECTION_H_ */
