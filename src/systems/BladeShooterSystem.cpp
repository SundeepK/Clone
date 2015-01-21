#include <systems/BladeShooterSystem.h>
#include <components/BladeComponent.h>
#include <vector>
#include <components/PhysicsComponent.h>
#include <components/BladeShooterComponent.h>
#include <game-objects/GameObjectTag.h>
#include <components/Texcoords.h>
#include <components/SplitDirectionComponent.h>
#include <components/TimeStepComponent.h>

class BladeShooterSystem::BladeShooterSystemImpl{

public:
	BladeShooterSystemImpl(b2World& box2dWorld) : m_box2dWorld(&box2dWorld) {}
	~BladeShooterSystemImpl(){}

	std::unique_ptr<b2World> m_box2dWorld;
	sf::Clock m_clock;

	void update(anax::World& world, std::vector<anax::Entity>& entities){

		auto allEntities =   world.getEntities();
		float timeStep = 0;
		bool isTimeSlowedDown = false;
		for(anax::Entity entity : allEntities){
			if(entity.isValid() && entity.hasComponent<TimeStepComponent>()){
				auto& timeStepComp = entity.getComponent<TimeStepComponent>();
				timeStep = timeStepComp.timeStep;
				isTimeSlowedDown = timeStepComp.isTimeSlowedDown;
				break;
			}
		}

		for(anax::Entity bladeShooterEntity : entities){

			if(!bladeShooterEntity.isValid()){
				continue;
			}

			sf::Time currentTime = m_clock.getElapsedTime();
			auto& bladeShooterComp = bladeShooterEntity.getComponent<BladeShooterComponent>();
			auto bladeShooterState = bladeShooterComp.bladeShooterState;
			if(bladeShooterState == BladeShooterState::NOT_STARTED){
				bladeShooterComp.lastTimeBladeShot = m_clock.getElapsedTime();
				bladeShooterComp.bladeShooterState = BladeShooterState::SHOOTING;
				createBlade(bladeShooterEntity);
			}else if(isTimeSlowedDown){
				sf::Time elaspedTime = (bladeShooterComp.lastTimeBladeShot + bladeShooterComp.slowedDownAccumulation);
				int diff = (elaspedTime - bladeShooterComp.lastTimeBladeShot).asMilliseconds();
				std::cout << "diff " << diff << std::endl;
				if(diff >= bladeShooterComp.delayBetweenBladeShots.asMilliseconds()){
					createBlade(bladeShooterEntity);
					bladeShooterComp.lastTimeBladeShot = elaspedTime;
					bladeShooterComp.slowedDownAccumulation =  sf::seconds(0);
				}else{
					bladeShooterComp.slowedDownAccumulation += sf::seconds(timeStep);
				}
			}else if((currentTime - bladeShooterComp.lastTimeBladeShot).asMilliseconds() >= bladeShooterComp.delayBetweenBladeShots.asMilliseconds()){
				createBlade(bladeShooterEntity);
				bladeShooterComp.lastTimeBladeShot = currentTime;
			}
		}
	}

	void createBlade(anax::Entity& entity){
		auto& bladeShooterComp = entity.getComponent<BladeShooterComponent>();
		auto& physicsComp = entity.getComponent<PhysicsComponent>();

		if(bladeShooterComp.previousBlades.size() > 0){
			if(bladeShooterComp.previousBlades[0].isValid() && bladeShooterComp.previousBlades[0].isActivated()){
				return;
			}else{
				bladeShooterComp.previousBlades.clear();
			}
		}

		b2Body* body = physicsComp.physicsBody;
		b2Vec2 startingPosition = body->GetPosition();
		auto& world = entity.getWorld();

		auto bladeEntity = world.createEntity();
		auto& bladeComp = bladeEntity.addComponent<BladeComponent>();
		auto& bladePhysicsComp = bladeEntity.addComponent<PhysicsComponent>();
		auto& texCoordsComp = bladeEntity.addComponent<Texcoords>();
		auto& splitDirectionComp = bladeEntity.addComponent<SplitDirectionComponent>();
		splitDirectionComp.splitDirection = Direction::NONE;

		bladeComp.bladeLinearVelocity = bladeShooterComp.bladeLinerVelocty;
		bladePhysicsComp.physicsBody = createBladeBody(startingPosition, bladeShooterComp.bladeSize);
		bladeEntity.activate();
		bladeShooterComp.previousBlades.push_back(bladeEntity);
	}

	b2Body* createBladeBody(b2Vec2 startingPosition, b2Vec2 shapeSize){
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position = startingPosition;
		b2PolygonShape shape;
		shape.SetAsBox(shapeSize.x, shapeSize.y);
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 1.0f;
		fd.filter.categoryBits = GameObjectTag::BLADE;
		fd.filter.maskBits =  ~GameObjectTag::BLADE_SHOOTER | ~GameObjectTag::NINJA_SENSE;

		b2Body* bladeBody  = m_box2dWorld->CreateBody(&bd);
		bladeBody->SetGravityScale(0.0f);
		bladeBody->CreateFixture(&fd);
		return bladeBody;
	}

};

BladeShooterSystem::BladeShooterSystem(b2World& box2dWorld) : Base(anax::ComponentFilter().requires<PhysicsComponent,BladeShooterComponent>()), m_impl(new BladeShooterSystemImpl(box2dWorld)) {
}

BladeShooterSystem::~BladeShooterSystem() {
}

void BladeShooterSystem::update(){
	auto entities = getEntities();
	m_impl->update( getWorld(), entities);
}



