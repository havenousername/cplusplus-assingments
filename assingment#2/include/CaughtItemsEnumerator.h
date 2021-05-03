#pragma once
#include <string>
#include <fstream>

struct CaughtItem
{
	std::string name;
	int countOftems;
};

class CaughtItemsEnumerator
{
private:
	CaughtItem _current;
	std::string _itemName;
	std::ifstream _file;
	bool _b_End;
public:
	enum FileErrors { MissingFileError };
	CaughtItemsEnumerator(const std::string& filename, const std::string& itemName) throw (FileErrors);
	void first() { next(); }
	void next();
	CaughtItem current() { return _current; }
	bool end() { return _b_End; }
};

