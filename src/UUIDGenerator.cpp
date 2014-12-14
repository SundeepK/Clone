#include <UUIDGenerator.h>


UUIDGenerator::UUIDGenerator() {
}

UUIDGenerator::~UUIDGenerator() {
}

std::string UUIDGenerator::createUuid() {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
	return boost::uuids::to_string(uuid);
}
