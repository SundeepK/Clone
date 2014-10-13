#include <systems/MouseSplitterSystem.h>
#include <Box2D/Box2D.h>

class MouseSplitterSystem::MouseSplitterSystemImpl{

public:

	MouseSplitterSystemImpl(B2dSplitter& m_b2dSplitter) : m_b2dSplitter(&m_b2dSplitter), m_sliceLine(sf::Lines, 2){
	}

	~MouseSplitterSystemImpl(){}

	std::unique_ptr<B2dSplitter> m_b2dSplitter;
    bool isleftPressed = false;
    sf::VertexArray m_sliceLine;

	void processLeftMousePressed(const sf::Event& event,  sf::Vector2f cameraPos){
		    if(isleftPressed) {
		          m_sliceLine[1].position = (sf::Vector2f(event.mouseMove.x + cameraPos.x, event.mouseMove.y + cameraPos.y));
		          m_sliceLine[1].color =     sf::Color::Red;
		      }

		    if (event.type == sf::Event::MouseButtonPressed) {
		        if (event.mouseButton.button == sf::Mouse::Left) {
		        	sf::Vector2f mousePos(event.mouseButton.x + cameraPos.x, event.mouseButton.y +cameraPos.y);
		            m_sliceLine[0].position = (mousePos);
		            m_sliceLine[0].color =     sf::Color::Red;
		            m_sliceLine[1].position = (mousePos);
		            m_sliceLine[1].color =     sf::Color::Red;
		            isleftPressed = true;
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


		void performBox2dSplit(const sf::Event& event,  sf::Vector2f cameraPos){
		    processLeftMousePressed(event, cameraPos);
		    processLeftMouseReleased(event, cameraPos);
		}

		void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			rt.draw(m_sliceLine);
		}

		void processMouseEvents(sf::RenderWindow& App, sf::Vector2f cameraPos) {
		    sf::Event event;
		    while( App.pollEvent(event)) {
		        if(event.type == sf::Event::Closed){
		                    App.close();
		        }
		        sf::Vector2f gg(App.getViewport(App.getView()).left, App.getViewport(App.getView()).top);
		        performBox2dSplit(event,cameraPos);
		    }
		}

};

MouseSplitterSystem::MouseSplitterSystem(B2dSplitter& b2dSplitter) :  m_impl(new MouseSplitterSystemImpl(b2dSplitter)){
}

MouseSplitterSystem::~MouseSplitterSystem() {
}

void MouseSplitterSystem::processMouseEventsForSplitter(sf::RenderWindow& App, sf::Vector2f cameraPos) {
	m_impl->processMouseEvents(App, cameraPos);
}

void MouseSplitterSystem::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

