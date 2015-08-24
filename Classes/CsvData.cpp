#include "CsvData.h"

void CsvData::addLineData(ValueVector lineData) {
	_data.push_back(Value(lineData));
}

ValueVector CsvData::getLineData(int lineNum) {
	return _data.at(lineNum).asValueVector();
}

Size CsvData::getRowColNum() {
	Size size = Size();
	size.width = _data.size();
	if (size.width > 0) {
		size.height = _data.at(0).asValueVector().size();
	}
	return size;
}

bool CsvData::init() {
	return true;
}