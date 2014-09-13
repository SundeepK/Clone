#ifndef BOX2DLEVELLOADER_H_
#define BOX2DLEVELLOADER_H_

#include <Box2D/Box2D.h>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <memory.h>

class TmxBox2dLevelLoader {
	public:
		TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory);
		virtual ~TmxBox2dLevelLoader();

		void loadLevel(std::string levelName, b2World& b2dworld);

	private:
		std::unique_ptr<tmx::MapLoader> m_mapLoader;
};

#endif /* BOX2DLEVELLOADER_H_ */
