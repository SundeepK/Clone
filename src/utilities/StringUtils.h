#ifndef SRC_UTILITIES_STRINGUTILS_H_
#define SRC_UTILITIES_STRINGUTILS_H_

#include <vector>
#include <string>

class StringUtils {
public:
	StringUtils();
	~StringUtils();


	static std::vector<float> parseListOfFloats(std::string stringToParse);
};

#endif /* SRC_UTILITIES_STRINGUTILS_H_ */
