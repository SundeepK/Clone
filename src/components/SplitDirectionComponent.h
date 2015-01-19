#ifndef SPLITDIRECTION_H_
#define SPLITDIRECTION_H_

#include <anax/Component.hpp>
#include <components/Direction.h>

class SplitDirectionComponent : public anax::Component<SplitDirectionComponent>{

public:
	Direction splitDirection;

};

#endif /* SPLITDIRECTION_H_ */
