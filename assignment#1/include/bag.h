#pragma once

#include <vector>
#include <utility>
#include <iostream>

class Bag
{
private:
	std::vector<std::pair<int, int>> pairs;
	int _unique_elements;
public:
	enum BagErrors { FOUND_ITEM_ERROR, OVERFLOW_ERROR, UNDERFLOW_ERROR };
	int size() const
	{
		return pairs.size();
	}

	int get_unique_element_count()
	{
		return _unique_elements;
	}

	Bag()
	{
	    _unique_elements = 0;
		pairs.clear();
	}
	~Bag() {}


	std::vector<std::pair<int, int>> getPairs()
	{
		return pairs;
	}

	// operators
	std::pair<int, int> operator[] (unsigned int i) const
	{
		if (i > pairs.size() - 1)
		{
			throw BagErrors::OVERFLOW_ERROR;
		}

		if (i < 0 || pairs.size() == 0)
		{
			throw BagErrors::UNDERFLOW_ERROR;
		}

		return pairs[i];
	}

	friend bool operator==(const std::pair<int, int>& i, const std::pair<int, int>& s)
	{
		return i.first == s.first && i.second == s.first;
	}

	void insert_entry(int item);
	void remove_entry(int item);
	void remove_entry();
	int frequency_of_element(int item) const;

	void print() const;
};

