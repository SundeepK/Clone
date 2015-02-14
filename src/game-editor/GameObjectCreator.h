#ifndef SRC_GAME_EDITOR_GAMEOBJECTCREATOR_H_
#define SRC_GAME_EDITOR_GAMEOBJECTCREATOR_H_

#include <vector>
#include <anax/World.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include <tmx/MapObject.h>
#include <game-objects/GameEntityCreator.h>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/SFGUI.hpp>
#include <game-editor/ObjectCreatorController.h>

class GameObjectCreator {
public:
	GameObjectCreator();
	~GameObjectCreator();

private:
	class GameObjectCreatorImpl;
	std::unique_ptr<GameObjectCreatorImpl> m_impl;
};

#endif /* SRC_GAME_EDITOR_GAMEOBJECTCREATOR_H_ */
