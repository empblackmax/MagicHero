#include "CsvUtil.h"
#include "StringUtil.h"

static CsvUtil* csvUtil = nullptr;
CsvUtil* CsvUtil::getInstance() {
	if (csvUtil == nullptr) {
		csvUtil = new CsvUtil();
	}
	return csvUtil;
}

CsvUtil::~CsvUtil() {
	delete csvUtil;
}

Value CsvUtil::getValue(int typeName, int property, const char *csvPath) {
	auto csvData = _dataMap.at(csvPath);
	if (csvData == nullptr) {
		this->loadFile(csvPath);
		csvData = _dataMap.at(csvPath);
	}
	ValueVector line = csvData->getLineData(typeName);
	return Value(line.at(property));
}

Value CsvUtil::getValueForAB(std::string typeName, ArrowAndBowProperty property, const char *csvPath) {
	std::string typeList[11] = BOW_LIST;
	int type = 0;
	for (int i = 0; i < 11; i++) {
		if (typeList[i].compare(typeName.c_str()) == 0) {
			type = i;
			break;
		}
	}
	return this->getValue(type, (int)property, csvPath);
}

Value CsvUtil::getValueForCard(int cardID, const char *csvPath) {
	return this->getValue(cardID, 1, csvPath);
}

void CsvUtil::loadFile(const char *csvPath) {
	CsvData *data = CsvData::create();
	std::string str = FileUtils::getInstance()->getStringFromFile(csvPath);
	ValueVector lineList = StringUtil::getInstance()->split(str.c_str(), "\n");

	for (auto value : lineList) {
		ValueVector line = StringUtil::getInstance()->split(value.asString().c_str(), ",");
		data->addLineData(line);
	}
	_dataMap.insert(csvPath, data);
}