#pragma once
#include "bag.h"
class Menu
{
public:
	Menu() : bag() {};
	void run();

private:
	Bag bag;

	void menu_write();
	void add_item();
	void remove_item();
	void get_frequency_of_item();
	void unique_elements_count();
	void bag_write();
	void input_number(int& num);
};


