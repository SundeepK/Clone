#ifndef SRC_UTILITIES_COLLISIONUTILS_H_
#define SRC_UTILITIES_COLLISIONUTILS_H_

#include <Box2D/Box2D.h>

class CollisionUtils {
public:
	CollisionUtils();
	~CollisionUtils();

	static bool isColliding(b2Contact* contactA, uint16 maskA, uint16 maskB);

};

#endif /* SRC_UTILITIES_COLLISIONUTILS_H_ */
