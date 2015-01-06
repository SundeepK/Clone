#ifndef SRC_COMPONENTS_NINJASENSECOMPONENT_H_
#define SRC_COMPONENTS_NINJASENSECOMPONENT_H_

#include <anax/Component.hpp>
#include <Box2D/Box2D.h>
//brief tag class for now
class NinjaSenseComponent  : public anax::Component<NinjaSenseComponent> {

public:

	b2Fixture* ninjaSenseFixture;
};


#endif /* SRC_COMPONENTS_NINJASENSECOMPONENT_H_ */
