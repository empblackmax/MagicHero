#ifndef __CSV_UTIL_H__
#define __CSV_UTIL_H__

#include "Support.h"
#include "CsvData.h"
#include "CsvEnum.h"
USING_NS_CC;

class CsvUtil {
public:
	static CsvUtil* getInstance();
	~CsvUtil();
	Value getValue(int typeName, int property, const char *csvPath);
	Value getValueForAB(std::string typeName, ArrowAndBowProperty property, const char *csvPath);
	Value getValueForCard(int cardID, const char *csvPath);
private:
	Map<std::string, CsvData *> _dataMap;
	void loadFile(const char *csvPath);
};

#endif