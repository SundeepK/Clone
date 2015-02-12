#ifndef SRC_GAME_EDITOR_OBJECTCREATORCONTROLLER_H_
#define SRC_GAME_EDITOR_OBJECTCREATORCONTROLLER_H_

#include <SFGUI/Widgets.hpp>
#include <SFGUI/SFGUI.hpp>
#include <vector>
#include <anax/World.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include <tmx/MapObject.h>
#include <game-objects/GameEntityCreator.h>

class ObjectCreatorController {
public:
	ObjectCreatorController(anax::World& anaxWorld, b2World& box2dWorld);
	~ObjectCreatorController();

	void addEntityCreator(std::string nameOfCreator, std::unique_ptr<GameEntityCreator> entityCreator);
	void attachTo(sfg::Box::Ptr window);
	tmx::MapObject createGameObjectAt(sf::Vector2i position);

private:
	class ObjectCreatorControllerImpl;
	std::unique_ptr<ObjectCreatorControllerImpl> m_impl;
};

#endif /* SRC_GAME_EDITOR_OBJECTCREATORCONTROLLER_H_ */
