#ifndef SRC_GAME_EDITOR_OBJECTCREATORCONTROLLER_H_
#define SRC_GAME_EDITOR_OBJECTCREATORCONTROLLER_H_

#include <SFGUI/Widgets.hpp>
#include <SFGUI/SFGUI.hpp>
#include <vector>
#include <memory>
#include <game-objects/GameEntityCreator.h>

class ObjectCreatorController {
public:
	ObjectCreatorController();
	~ObjectCreatorController();

	void addEntityCreator(std::string nameOfCreator, std::unique_ptr<GameEntityCreator> entityCreator);
	void attachTo(sfg::Table::Ptr window);

private:
	class ObjectCreatorControllerImpl;
	std::unique_ptr<ObjectCreatorControllerImpl> m_impl;
};

#endif /* SRC_GAME_EDITOR_OBJECTCREATORCONTROLLER_H_ */
