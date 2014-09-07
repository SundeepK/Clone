#ifndef BOX2DLEVELLOADER_H_
#define BOX2DLEVELLOADER_H_

#include <Box2D/Box2D.h>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <memory.h>

class Box2dLevelLoader {
	public:
		Box2dLevelLoader(b2World& b2dworld, tmx::MapLoader& mapLoader);
		virtual ~Box2dLevelLoader();

		void loadLevel(std::string levelName, b2World& b2dworld);

	private:
		b2World m_b2World;
		std::unique_ptr<tmx::MapLoader> m_mapLoader;
};

#endif /* BOX2DLEVELLOADER_H_ */
