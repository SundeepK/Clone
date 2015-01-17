#include <utilities/CollisionUtils.h>

CollisionUtils::CollisionUtils() {
}

CollisionUtils::~CollisionUtils() {
}


bool CollisionUtils::isColliding(b2Contact* contact, uint16 maskA, uint16 maskB) {
	auto fixtureA = contact->GetFixtureA();
	auto fixtureB = contact->GetFixtureB();

	auto filterDataA = fixtureA->GetFilterData();
	auto filterDataB = fixtureB->GetFilterData();

	if (((filterDataA.categoryBits & maskA) == maskA && (filterDataB.categoryBits & maskB) == maskB)
			|| ((filterDataB.categoryBits & maskA) == maskA && (filterDataA.categoryBits & maskB) == maskB)) {
		return true;
	}

	return false;
}
