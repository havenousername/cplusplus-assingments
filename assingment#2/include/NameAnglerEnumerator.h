#pragma once
#include <string>
#include <fstream>
#include "CaughtItemsEnumerator.h"

struct NameAngler
{
	std::string name;
	int sumOfItems;
};

class NameAnglerEnumerator
{
private:
	CaughtItemsEnumerator _caughtEnor;
	NameAngler _current;
	std::ifstream _file;
	bool _b_End;

public:
	enum FileErrors { MissingFileError };
	NameAnglerEnumerator(const std::string& filename, const std::string& itemName) : _caughtEnor(filename, itemName) {};
	void first()
	{
		_caughtEnor.first();
		next();
	}
	void next();
	NameAngler current() { return _current; }
	bool end() { return _b_End; }
};

