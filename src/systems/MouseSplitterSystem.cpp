#include <systems/MouseSplitterSystem.h>
#include <Box2D/Box2D.h>
#include <components/PlayerControls.h>
#include <components/PlayerStateComponent.h>
#include <components/PhysicsComponent.h>
#include <components/PlayerTagComponent.h>
#include <tmx/Helpers.h>
#include <math.h>

class MouseSplitterSystem::MouseSplitterSystemImpl{

public:

	MouseSplitterSystemImpl(B2dSplitter& m_b2dSplitter) : m_b2dSplitter(&m_b2dSplitter), m_sliceLine(sf::Lines, 2){
	}

	~MouseSplitterSystemImpl(){}

	std::unique_ptr<B2dSplitter> m_b2dSplitter;
    bool isleftPressed = false;
    sf::VertexArray m_sliceLine;
    const float SPLITTER_LENGTH_LIMIT = 170;

    sf::Vector2f getSplitterVec(const sf::Vector2f& playerPos, const sf::Vector2f& mousePos){
		sf::Vector2f splitterVec = mousePos;
    	sf::Vector2f difference = mousePos - playerPos;
    	float length = Helpers::Vectors::GetLength(difference);
    	if(length > SPLITTER_LENGTH_LIMIT){
    		splitterVec.x = playerPos.x + (SPLITTER_LENGTH_LIMIT/length) * (mousePos.x - playerPos.x);
    		splitterVec.y = playerPos.y + (SPLITTER_LENGTH_LIMIT/length) * (mousePos.y - playerPos.y);
    	}
    	return splitterVec;
    }

    void onLeftClick(const sf::Event& event,  sf::Vector2f cameraPos, sf::Vector2f playerPos){
    	//	m_b2dSplitter->refreshEntityBodyTypes();
	        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
	        	m_b2dSplitter->clearIntersects();
	        	sf::Vector2f mousePos(event.mouseButton.x + cameraPos.x, event.mouseButton.y +cameraPos.y);
	        	sf::Vector2f endSplitLineVec = getSplitterVec(playerPos, mousePos);

	            m_sliceLine[0].position = playerPos;
	            m_sliceLine[0].color =     sf::Color::Red;
	            m_sliceLine[1].position = endSplitLineVec;
	            m_sliceLine[1].color =     sf::Color::Red;
	            if( !(m_sliceLine[0].position == m_sliceLine[1].position)) {
	            	performRayCastForSplitter();
	            }
	            m_b2dSplitter->deleteEntities();
	    }
    }

	void processLeftMousePressed(const sf::Event& event,  sf::Vector2f cameraPos){
		    if (event.type == sf::Event::MouseButtonPressed) {
		        if (event.mouseButton.button == sf::Mouse::Left) {
		        	sf::Vector2f mousePos(event.mouseButton.x + cameraPos.x, event.mouseButton.y +cameraPos.y);
		            m_sliceLine[0].position = (mousePos);
		            m_sliceLine[0].color =     sf::Color::Red;
		            m_sliceLine[1].position = (mousePos);
		            m_sliceLine[1].color =     sf::Color::Red;
		        }
		    }
		}

		void processLeftMouseReleased(const sf::Event& event,  sf::Vector2f cameraPos){
		    if (event.type == sf::Event::MouseButtonReleased) {
		        if (event.mouseButton.button == sf::Mouse::Left) {
		        	m_b2dSplitter->clearIntersects();
		        	sf::Vector2f mousePos(event.mouseButton.x + cameraPos.x, event.mouseButton.y + cameraPos.y);
		            m_sliceLine[1].position = (mousePos);
		            m_sliceLine[1].color =     sf::Color::Red;
		            isleftPressed = false;
		            if( !(m_sliceLine[0].position == m_sliceLine[1].position)) {
		            	performRayCastForSplitter();
		            }
		            m_b2dSplitter->deleteEntities();
		        }
		    }
		}


		void performRayCastForSplitter(){
			Vec startLine = m_sliceLine[0].position;
			Vec endLine = m_sliceLine[1].position;
			b2Vec2 s =  startLine.pixToM().toB2v();
			b2Vec2 e = endLine.pixToM().toB2v();
			m_b2dSplitter->split(s, e);
		}


		void performBox2dSplit(const sf::Event& event,  sf::Vector2f cameraPos, b2Body* playerBody){

			Vec playerPos(playerBody->GetPosition());
			onLeftClick(event, cameraPos, playerPos.mToPix().toSFMLv());
//		    processLeftMousePressed(event, cameraPos);
//		    processLeftMouseReleased(event, cameraPos);
		}

		void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			rt.draw(m_sliceLine);
		}

		void processMouseEvents(std::vector<sf::Event>& events, sf::Vector2f cameraPos, std::vector<anax::Entity>& entites) {
			for (auto entity : entites) {
		    	for(sf::Event event : events){
		   //     sf::Vector2f gg(App.getViewport(App.getView()).left, App.getViewport(App.getView()).top);
	    		auto& physicsComponent = entity.getComponent<PhysicsComponent>();
	    		b2Body* body = physicsComponent.physicsBody;

		        performBox2dSplit(event,cameraPos, body);
		    }
			}
		}

};

MouseSplitterSystem::MouseSplitterSystem(B2dSplitter& b2dSplitter) : Base(anax::ComponentFilter().requires<PlayerTagComponent, PhysicsComponent>()),
											m_impl(new MouseSplitterSystemImpl(b2dSplitter)){
}

MouseSplitterSystem::~MouseSplitterSystem() {
}

void MouseSplitterSystem::processMouseEventsForSplitter(std::vector<sf::Event>& events, sf::Vector2f cameraPos) {
    auto entities = getEntities();
	m_impl->processMouseEvents(events, cameraPos, entities);
}

void MouseSplitterSystem::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

