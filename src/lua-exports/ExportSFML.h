#include "ExportableToLua.h"
#include <memory.h>

#ifndef SRC_LUA_EXPORTS_EXPORTSFML_H_
#define SRC_LUA_EXPORTS_EXPORTSFML_H_

class ExportSFML : public ExportableToLua{
public:

	ExportSFML();
	~ExportSFML();

	void exportToLua(lua_State *myLuaState);


private:
	class ExportSFMLImpl;
	std::unique_ptr<ExportSFMLImpl> m_impl;
};


#endif /* SRC_LUA_EXPORTS_EXPORTSFML_H_ */
