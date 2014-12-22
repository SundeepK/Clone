/*
 * IgnoreCollisionComponent.h
 *
 *  Created on: 22 Dec 2014
 *      Author: sundeep
 */

#ifndef SRC_COMPONENTS_IGNORECOLLISIONCOMPONENT_H_
#define SRC_COMPONENTS_IGNORECOLLISIONCOMPONENT_H_

#include <SFML/System.hpp>

enum IgnoreCollisionReason {
	NEW_SPLIT_BODY = 0
};

class IgnoreCollisionComponent  : public anax::Component<IgnoreCollisionComponent> {

	public:
		sf::Time timeIgnoreCollisionAdded;
		IgnoreCollisionReason reason;
};





#endif /* SRC_COMPONENTS_IGNORECOLLISIONCOMPONENT_H_ */
