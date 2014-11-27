#include <lua-exports/ExportBox2d.h>

class ExportBox2d::ExportBox2dImpl{

public:

	ExportBox2dImpl(){}
	~ExportBox2dImpl(){}

	void exportToLua(lua_State *myLuaState){

	}

};


ExportBox2d::ExportBox2d() : m_impl(new ExportBox2dImpl()) {

}

ExportBox2d::~ExportBox2d() {
}

void ExportBox2d::exportToLua(lua_State *luaState){
	m_impl->exportToLua(luaState);
}



