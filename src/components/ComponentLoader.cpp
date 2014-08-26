#include <components/ComponentLoader.h>

extern "C"
{
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}

#include <memory.h>
#include <luabind/luabind.hpp>
#include <iostream>

ComponentLoader::ComponentLoader()  {

}

ComponentLoader::~ComponentLoader() {
}

void ComponentLoader::loadPlayerComponents() {

    lua_State *myLuaState = luaL_newstate();

    luabind::open(myLuaState);
	luaL_openlibs(myLuaState);

	if(luaL_dofile(myLuaState, "lua-configs/playerConfig.lua")){
        printf("%s\n", lua_tostring(myLuaState, -1));
	}

	luabind::module(myLuaState)[
	luabind::class_<PhysicsComponent>("PhysicsComponent")
	      .def(luabind::constructor<>())
	      .def_readwrite("previousAngle", &PhysicsComponent::previousAngle)
	];

	PhysicsComponent physicsComp;
	try {
	    luabind::call_function<void>(myLuaState, "loadPlayerComponent", &physicsComp);
	} catch (luabind::error& e) {
	    std::string error = lua_tostring(e.state(), -1);
	    std::cout << error << std::endl;
	}

	std::cout << physicsComp.previousAngle << std::endl;

    lua_close(myLuaState);
}
