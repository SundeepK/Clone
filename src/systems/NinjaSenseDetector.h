#ifndef SRC_SYSTEMS_NINJASENSEDETECTOR_H_
#define SRC_SYSTEMS_NINJASENSEDETECTOR_H_

#include <memory>
#include <anax/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class NinjaSenseDetector : public anax::System<NinjaSenseDetector> , public sf::Drawable {
public:
	NinjaSenseDetector(b2World& b2world);
	~NinjaSenseDetector();

	void checkForEntitiesAffectedByNinjaSense();


private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;


	class NinjaSenseDetectorImpl;
	std::unique_ptr<NinjaSenseDetector> m_impl;

};

#endif /* SRC_SYSTEMS_NINJASENSEDETECTOR_H_ */
