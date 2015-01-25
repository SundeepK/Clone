#include <systems/LevelRestartSystem.h>
#include <components/PlayerDeadComponent.h>
#include <iostream>

class LevelRestartSystem::LevelRestartSystemImpl{
public:
	LevelRestartSystemImpl(TmxBox2dLevelLoader& levelLoader) : m_tmxLoader(&levelLoader) {}
	~LevelRestartSystemImpl(){}

	std::unique_ptr<TmxBox2dLevelLoader> m_tmxLoader;

	void update(std::vector<anax::Entity>& entities) {
		if(entities.size() > 0){
			std::cout << "restartinmg level" << std::endl;
			m_tmxLoader->restartLevel();
		}
	}


};


LevelRestartSystem::LevelRestartSystem(TmxBox2dLevelLoader& levelLoader) : Base(anax::ComponentFilter().requires<PlayerDeadComponent>()), m_impl(new LevelRestartSystemImpl(levelLoader)) {

}

LevelRestartSystem::~LevelRestartSystem() {

}

void LevelRestartSystem::update() {
	auto entities = getEntities();
	m_impl->update(entities);
}
