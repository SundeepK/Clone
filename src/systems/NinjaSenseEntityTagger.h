#ifndef SRC_SYSTEMS_NINJASENSEDETECTOR_H_
#define SRC_SYSTEMS_NINJASENSEDETECTOR_H_

#include <anax/anax.hpp>
#include <Box2D/Box2D.h>
#include <memory>

class NinjaSenseEntityTagger: public b2QueryCallback, public anax::System<NinjaSenseEntityTagger>  {
public:

	NinjaSenseEntityTagger();
	~NinjaSenseEntityTagger();

	bool ReportFixture(b2Fixture* fixture);


private:

	class NinjaSenseEntityTaggerImpl;
	std::unique_ptr<NinjaSenseEntityTaggerImpl> m_impl;

};

#endif /* SRC_SYSTEMS_NINJASENSEDETECTOR_H_ */
