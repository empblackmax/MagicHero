#include "StringUtil.h"

static StringUtil *stringUtil = nullptr;

StringUtil* StringUtil::getInstance() {
	if (stringUtil == nullptr) {
		stringUtil = new StringUtil();
	}
	return stringUtil;
}

StringUtil::~StringUtil() {
	delete stringUtil;
}

ValueVector StringUtil::split(const char *srcStr, const char *mark) {
	ValueVector stringList;
	int size = strlen(srcStr);

	Value str = Value(srcStr);

	int startIndex = 0;
	int endIndex = 0;

	endIndex = str.asString().find(mark);

	std::string lineStr;
	while (endIndex > 0) {
		lineStr = str.asString().substr(startIndex, endIndex);
		stringList.push_back(Value(lineStr));
		
		str = Value(str.asString().substr(endIndex + 1, size));
		endIndex = str.asString().find(mark);
	}
	
	if (str.asString().compare("") != 0) {
		stringList.push_back(str);
	}

	return stringList;
}