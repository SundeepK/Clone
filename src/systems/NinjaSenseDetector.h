#ifndef SRC_SYSTEMS_NINJASENSEDETECTOR_H_
#define SRC_SYSTEMS_NINJASENSEDETECTOR_H_

#include <memory>
#include <anax/System.hpp>

class NinjaSenseDetector : public anax::System<NinjaSenseDetector> , public sf::Drawable {
public:
	NinjaSenseDetector(b2World& b2world);
	~NinjaSenseDetector();

	void checkForEntitiesAffectedByNinjaSense();


private:

	class NinjaSenseDetectorImpl;
	std::unique_ptr<NinjaSenseDetector> m_impl;

};

#endif /* SRC_SYSTEMS_NINJASENSEDETECTOR_H_ */
