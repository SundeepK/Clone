#ifndef COMPONENTLOADER_H_
#define COMPONENTLOADER_H_

#include <components/PhysicsComponent.h>

class ComponentLoader {
public:



	ComponentLoader();
	virtual ~ComponentLoader();

	void loadPlayerComponents();


 //   std::unique_ptr<lua_State>  m_luaState;

};

#endif /* COMPONENTLOADER_H_ */