#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include "Support.h"
USING_NS_CC;

class StringUtil {
public:
	static StringUtil* getInstance();
	~StringUtil();

	//ÇÐ·Ö×Ö·û´®
	ValueVector split(const char *srcStr, const char *mark);
};

#endif