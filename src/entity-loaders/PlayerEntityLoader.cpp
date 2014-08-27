#include <entity-loaders/PlayerEntityLoader.h>

void PlayerEntityLoader::loadEntity(anax::World& anaxWorld,lua_State* myLuaState) {

	luabind::module(myLuaState)[
	luabind::class_<PhysicsComponent>("PhysicsComponent")
	      .def(luabind::constructor<>())
	      .def_readwrite("previousAngle", &PhysicsComponent::previousAngle)
	      .def_readwrite("previousPosition", &PhysicsComponent::previousPosition)
	];


	PhysicsComponent physicsComp;
	try {
	    luabind::call_function<void>(myLuaState, "loadPlayerComponent", &physicsComp);
	} catch (luabind::error& e) {
	    std::string error = lua_tostring(e.state(), -1);
	    std::cout << error << std::endl;
	}

	std::cout << physicsComp.previousPosition.x << std::endl;
}
