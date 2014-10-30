#ifndef SPLITDIRECTION_H_
#define SPLITDIRECTION_H_

#include <anax/Component.hpp>

enum class SplitDirection {
		RIGHT = 1,
		LEFT,
		TOP,
		DOWN
};


class SplitDirectionComponent : public anax::Component<SplitDirectionComponent>{


};

#endif /* SPLITDIRECTION_H_ */
