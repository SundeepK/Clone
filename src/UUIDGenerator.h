#ifndef UUIDGENERATOR_H_
#define UUIDGENERATOR_H_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class UUIDGenerator {
public:
	UUIDGenerator();
	virtual ~UUIDGenerator();

	static std::string createUuid();

};


#endif /* UUIDGENERATOR_H_ */
