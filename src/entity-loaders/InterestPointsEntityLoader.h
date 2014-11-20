#ifndef INTERESTPOINTSENTITYLOADER_H_
#define INTERESTPOINTSENTITYLOADER_H_


#include <entity-loaders/LuaEntityLoader.h>
#include <components/Sensors.h>
#include <B2Builder.h>
#include <B2BoxBuilder.h>
#include <components/SensorComponent.h>
#include <memory>

class InterestPointsEntityLoader : public LuaEntityLoader {
public:

	InterestPointsEntityLoader();

	~InterestPointsEntityLoader();

	void loadEntity(anax::World& anaxWorld, b2World& box2dWorld,  std::unordered_map<std::string, tmx::MapObject>& loadedMapData,  lua_State *myLuaState);

private:

	class InterestPointsEntityLoaderImpl;
	std::unique_ptr<InterestPointsEntityLoaderImpl> m_impl;

};


#endif /* INTERESTPOINTSENTITYLOADER_H_ */
