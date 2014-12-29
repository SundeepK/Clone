extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <iostream>
#include <lua-exports/ExportSFML.h>
#include <SFML/System.hpp>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>

class ExportSFML::ExportSFMLImpl{


public:
	ExportSFMLImpl(){}

	~ExportSFMLImpl(){}

	 void exportToLua(lua_State *luaState){
			luabind::module(luaState)[
			luabind::class_<sf::Vector2f>("sf_Vector2f")
			      .def(luabind::constructor<>())
				  .def_readwrite("x", &sf::Vector2f::x)
				  .def_readwrite("y", &sf::Vector2f::y)
			];

			luabind::module(luaState)[
				luabind::class_<sf::FloatRect>("sf_FloatRect")
				      .def(luabind::constructor<>())
					  .def_readwrite("left", &sf::FloatRect::left)
					  .def_readwrite("top", &sf::FloatRect::top)
					  .def_readwrite("width", &sf::FloatRect::width)
					  .def_readwrite("height", &sf::FloatRect::height)

				];

			luabind::module(luaState)[
			luabind::class_<tmx::MapObject>("tmx_MapObject")
			      .def(luabind::constructor<>())
				  .def("GetPropertyString", (std::string (tmx::MapObject::*) (const std::string& name) ) &tmx::MapObject::GetPropertyString)
				  .def("GetPosition",  (sf::Vector2f (tmx::MapObject::*) () const ) &tmx::MapObject::GetPosition)
				  .def("GetCentre",  (sf::Vector2f (tmx::MapObject::*) () const ) &tmx::MapObject::GetCentre)
				  .def("GetAABB",  (sf::FloatRect (tmx::MapObject::*) () const ) &tmx::MapObject::GetAABB)
			];

			luabind::module(luaState)[
			luabind::class_<sf::Time>("sf_Time")
			      .def(luabind::constructor<>())
				  .def("asSeconds",  &sf::Time::asSeconds)
				  .def("asMilliseconds",  &sf::Time::asMilliseconds)

			];

			luabind::module(luaState)[
			luabind::class_<sf::Clock>("sf_Clock")
			      .def(luabind::constructor<>())
				  .def("getElapsedTime",  &sf::Clock::getElapsedTime)
			];

	 }




};

ExportSFML::ExportSFML() : m_impl(new ExportSFMLImpl()) {
}

ExportSFML::~ExportSFML() {
}

void ExportSFML::exportToLua(lua_State* luaState) {
	m_impl->exportToLua(luaState);
}
