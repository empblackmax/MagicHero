#ifndef __CSV_DATA_H__
#define __CSV_DATA_H__

#include "Support.h"
USING_NS_CC;

class CsvData : public Ref {
public:
	CREATE_FUNC(CsvData);
	void addLineData(ValueVector lineData);
	ValueVector getLineData(int lineNum);
	//返回size中height表示每行数据数，width表示数据条数
	Size getRowColNum();	
protected:
	bool init();
private:
	ValueVector _data;
};

#endif