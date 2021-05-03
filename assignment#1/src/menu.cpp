#include "menu.h"
#include "bag.h"
#include <iostream>
#include <limits>


void Menu::run()
{
	int action = 0;
	do {
		menu_write();
		std::cout << std::endl << ">>>>";
		std::cin >> action;
		switch (action)
		{
		case 1:
			add_item();
			break;
		case 2:
			remove_item();
			break;
		case 3:
			get_frequency_of_item();
			break;
		case 4:
			unique_elements_count();
			break;
		case 5:
			bag_write();
			break;
		default:
			break;
		}
	} while (action != 0);
}

void Menu::menu_write()
{
	std::cout << std::endl << std::endl;
	std::cout << "Please select your action\n";
	std::cout << "0. - Quit" << std::endl;
	std::cout << "1. - Add element to the bag" << std::endl;
	std::cout << "2. - Remove element from the bag" << std::endl;
	std::cout << "3. - Get frequency of an item" << std::endl;
	std::cout << "4. - Get count of unique elements from the bag" << std::endl;
	std::cout << "5. - Write the bag" << std::endl;
}

void Menu::input_number(int& number)
{
	std::cin >> number;
	int imin = std::numeric_limits<int>::min();
    int imax = std::numeric_limits<int>::max();
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Your input is wrong. Please input number in range between " << imin << " - " << imax << " " << std::endl;
		std::cin >> number;
	}
}

void Menu::add_item()
{
	std::cout << "Please insert new item" << std::endl;
	int item;
	input_number(item);
	try
	{
		bag.insert_entry(item);
	}
	catch (Bag::BagErrors e)
	{
		if (e == Bag::OVERFLOW_ERROR)
		{
			std::cout << "OVERFLOW ERROR! Bag is full. Please consider deleting some elements from it first\n";
		}
	}
}

void Menu::remove_item()
{
	std::cout << "Please insert an item you want to delete" << std::endl;
	int item;
	input_number(item);
	try
	{
		if (item == bag[bag.size() - 1].first)
		{
			bag.remove_entry();
		}
		else {
			bag.remove_entry(item);
		}
	}
	catch (Bag::BagErrors e)
	{
		if (e == Bag::UNDERFLOW_ERROR)
		{
			std::cout << "UNDERFLOW ERROR! Bag is empty. Please consider adding some elements before\n";
		}
		else if (e == Bag::FOUND_ITEM_ERROR)
		{
			std::cout << "FOUND ITEM ERROR! Could not find such element in the bag.\n";
		}
	}
}

void Menu::get_frequency_of_item()
{
	std::cout << "Please insert an element whose frequency you wan to see" << std::endl;
	int item;
	input_number(item);


	try
	{
		int frequency = bag.frequency_of_element(item);
		std::cout << "Frequency of " << item << " is: " << frequency << std::endl;

	}
	catch (Bag::BagErrors e)
	{
		if (e == Bag::FOUND_ITEM_ERROR)
		{
			std::cout << "FOUND ITEM ERROR! Such element does not exist in the bag\n";
		}
	}

}

void Menu::unique_elements_count()
{
	std::cout << "Number of unique elements in bag is " << bag.get_unique_element_count();
}

void Menu::bag_write()
{
	bag.print();
}
