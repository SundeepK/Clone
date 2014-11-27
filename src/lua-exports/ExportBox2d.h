#ifndef EXPORTBOX2D_H_
#define EXPORTBOX2D_H_

#include <Box2D/Box2D.h>
#include "ExportableToLua.h"
#include <memory.h>

class ExportBox2d : public ExportableToLua{
public:

	ExportBox2d();
	~ExportBox2d();

	void exportToLua(lua_State *myLuaState);


private:
	class ExportBox2dImpl;
	std::unique_ptr<ExportBox2dImpl> m_impl;
};

#endif /* EXPORTBOX2D_H_ */
