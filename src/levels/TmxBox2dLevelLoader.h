#ifndef BOX2DLEVELLOADER_H_
#define BOX2DLEVELLOADER_H_

#include <Box2D/Box2D.h>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <anax/World.hpp>
#include <sstream>
#include <memory.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <opengl/TextureLoader.h>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>


class TmxBox2dLevelLoader {
	public:
		TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory);
		virtual ~TmxBox2dLevelLoader();

		void loadLevel(std::string levelName, b2World& b2dworld, anax::World& anaxWorld);

	private:
		void loadSplittableObjects(tmx::MapObjects& mapObject, anax::World& anaxWorld, b2World& b2dworld);
		void loadStaticObjects(const tmx::MapObjects& mapObject, b2World& b2dworld);
		void loadTmxLayerForLevel(tmx::MapLayer& layer, b2World& b2dworld, anax::World& anaxWorld);

		std::unique_ptr<tmx::MapLoader> m_mapLoader;
		TextureLoader m_textureLoader;
};

#endif /* BOX2DLEVELLOADER_H_ */
