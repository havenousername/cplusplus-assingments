#include "bag.h"
#include <iostream>
#include <iomanip>

void Bag::insert_entry(int item)
{

	bool contains_item = false;
	unsigned int i = 0;
	while (!contains_item && i < pairs.size())
	{
		contains_item = pairs[i].first == item;
		i++;
	}

	if (contains_item)
	{
		--i;
		if (pairs[i].second == 1)
        {
            _unique_elements--;
        }
        pairs[i].second += 1;
	}
	else
	{
		_unique_elements++;
		pairs.push_back({ item , 1 });
	}
}

void Bag::remove_entry(int item)
{
	if (pairs.size() == 0) {
		throw BagErrors::UNDERFLOW_ERROR;
	}

	bool contains_item = false;
	bool is_unique = true;

	unsigned int i = 0;
	while (!contains_item && i < pairs.size())
	{
		contains_item = item == pairs[i].first;
		if (contains_item)
		{
			is_unique = pairs[i].second == 1;
			break;
		}
		i++;
	}

	if (contains_item && is_unique)
	{
		_unique_elements--;
		pairs.erase(pairs.begin() + i);
	}
	else if (contains_item && !is_unique)
	{
		pairs[i].second -= 1;
		if (pairs[i].second == 1)
		{
			_unique_elements++;
		}
	}
	else
	{
		throw BagErrors::FOUND_ITEM_ERROR;
	}
}

void Bag::remove_entry()
{
	if (pairs.size() == 0) {
		throw BagErrors::UNDERFLOW_ERROR;
	}
	const int index = pairs.size() - 1;

	const int last_frequency = pairs[index].second;
	if (last_frequency > 1)
	{
		pairs[index].second -= 1;
		if (pairs[index].second == 1)
		{
			_unique_elements++;
		}
	}
	else
	{
		pairs.pop_back();
		_unique_elements--;
	}
}

int Bag::frequency_of_element(int item) const
{
	if (pairs.size() == 0)
	{
		throw BagErrors::FOUND_ITEM_ERROR;
	}
	bool contains_item = false;

	for (unsigned int i = 0; i < pairs.size(); i++)
	{
		contains_item = item == pairs[i].first;
		if (contains_item)
		{
			return pairs[i].second;
		}
	}

	throw BagErrors::FOUND_ITEM_ERROR;
}

void Bag::print() const
{
	if (pairs.size() == 0) {
		std::cout << "{}";
		return;
	}
	std::cout << "{\n";

	for (unsigned int i = 0; i < pairs.size(); i++) {
		std::cout << std::setw(14);
		std::cout << "{ element: " << pairs[i].first;
		std::cout << ", frequency: " << pairs[i].second;
		std::cout << " }" << std::endl;
	}

	std::cout << "}\n";
}





