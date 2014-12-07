#ifndef BOX2DLEVELLOADER_H_
#define BOX2DLEVELLOADER_H_

#include <Box2D/Box2D.h>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <sstream>
#include <memory.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <opengl/TextureLoader.h>
#include <components/SplitDirectionComponent.h>
#include <unordered_map>
#include <entity-loaders/WorldEntityLoader.h>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>


struct LevelObject{
	std::string levelMapName;
	std::string scriptName;
};

class TmxBox2dLevelLoader :  public anax::System<TmxBox2dLevelLoader>{
	public:
		TmxBox2dLevelLoader(tmx::MapLoader& mapDirectory, b2World& b2dworld, anax::World& anaxWorld);
		virtual ~TmxBox2dLevelLoader();

		void loadNextLevel();

	private:

		class TmxBox2dLevelLoaderImpl;
		std::unique_ptr<TmxBox2dLevelLoaderImpl> m_impl;

};

#endif /* BOX2DLEVELLOADER_H_ */
