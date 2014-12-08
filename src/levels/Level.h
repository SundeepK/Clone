#ifndef LEVEL_H_
#define LEVEL_H_


extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}

#include <luabind/luabind.hpp>

class Level {
public:
	Level() {

	}
	virtual ~Level(){

	}

	virtual void loadLevel(std::unordered_map<std::string, tmx::MapObject>& levelObjects) = 0;
	virtual void updateLevel() = 0;
	virtual void endLevel() = 0;


};



#endif /* LEVEL_H_ */
