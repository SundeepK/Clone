#ifndef EXPORTABLETOLUA_H_
#define EXPORTABLETOLUA_H_


extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}

#include <luabind/luabind.hpp>

class ExportableToLua {
public:
	ExportableToLua();
	virtual ~ExportableToLua();

	virtual void exportToLua(lua_State *myLuaState) = 0;

};

#endif /* EXPORTABLETOLUA_H_ */
