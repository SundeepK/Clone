#ifndef SRC_SYSTEMS_NINJASENSEDETECTOR_H_
#define SRC_SYSTEMS_NINJASENSEDETECTOR_H_

#include <memory>
#include <anax/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <systems/NinjaSenseEntityTagger.h>

class NinjaSenseDetector : public anax::System<NinjaSenseDetector> , public sf::Drawable {
public:
	NinjaSenseDetector(b2World& b2world, NinjaSenseEntityTagger& ninjaSenseEntityTrigger);
	~NinjaSenseDetector();

	void checkForEntitiesAffectedByNinjaSense();


private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;


	class NinjaSenseDetectorImpl;
	std::unique_ptr<NinjaSenseDetectorImpl> m_impl;

};

#endif /* SRC_SYSTEMS_NINJASENSEDETECTOR_H_ */
